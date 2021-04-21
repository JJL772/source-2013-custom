//===========================================================================//
// Name: vr_main.cpp
// Purpose: Main implementation of VR support using OpenXR
//===========================================================================//

/* OpenVR stuff (Must come first due to min/max BS) */
#include <openvr.h>

#include "tier1/strtools.h"
#include "tier1/tier1.h"
#include "tier1/convar.h"
#include "tier2/tier2.h"
#include "appframework/IAppSystem.h"
#include "appframework/AppFramework.h"
#include "materialsystem/imaterialsystem.h"
#include "tier0/icommandline.h"
#include "engine/ivdebugoverlay.h"
#include "appframework/ilaunchermgr.h"
#include "materialsystem/itexture.h"
#include "materialsystem/imaterial.h"
#include "shaderapi/ishaderapi.h"
#include "shaderapi/IShaderDevice.h"

#include "togl/linuxwin/dxabstract.h"
#include "togl/linuxwin/glbase.h"
#include "togl/linuxwin/glmgr.h"

#include "vr/vr.h"

#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>

IVDebugOverlay *g_pDebugOverlay = nullptr;
ILauncherMgr* g_pLauncherMgr = nullptr;

//=================================================================================================================//

class CSourceVR : public CTier2AppSystem<IVRClient>
{
	typedef CTier2AppSystem<IVRClient> BaseClass;

public:
	/* IAppSystem */
	bool Connect(CreateInterfaceFn factory) override;
	void Disconnect() override;
	InitReturnVal_t Init() override;
	void Shutdown() override;

	/* IVR */
	IVRHooks *GetHooks() override;
	void GetViewportBounds(EVRView view, int &x, int &y, int &w, int &h) override;

public:
	ITexture *m_vrRight;
	ITexture *m_vrLeft;

	/* OpenVR properties */
	vr::IVRSystem* m_vrSystem;
	
	SDL_Window* m_gameWindow = nullptr;
	SDL_GLContext m_glContext = nullptr;
	
	SDL_Window* m_debugWindow = nullptr;
	SDL_GLContext m_debugContext = nullptr;
	
	CGLMTex* m_texVrRight;
	CGLMTex* m_texVrLeft;
};

class CVRClientHooks : public IVRHooks
{
public:
	CSourceVR *m_vr;

	CVRClientHooks(CSourceVR *vr)
	{
		m_vr = vr;
	}

	/* Client only hooks. Not called on server */
	void PreRender() override;
	void Update(float frametime) override;
	void PostRender() override;
	void Draw(EVRView eye) override;

	/* Server only hooks. Not called on client */
	void FrameUpdatePreEntityThink() override;
	void FrameUpdatePostEntityThink() override;
	void PreClientUpdate() override;

	/* Called on both client and server */
	void OnSave() override;
	void OnRestore() override;
	void LevelInitPreEntity() override;
	void LevelInitPostEntity() override;
	void LevelShutdownPreEntity() override;
	void LevelShutdownPostEntity() override;
};

static CSourceVR gClientVR;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CSourceVR, IVRClient, VRCLIENT_MODULE_VERSION, gClientVR);

//=================================================================================================================//

bool CSourceVR::Connect(CreateInterfaceFn factory)
{
	BaseClass::Connect(factory);

	DevMsg("Connected vr.so\n");

	if (!g_pMaterialSystem)
	{
		Warning("[VR] g_pMaterialSystem was null\n");
		return false;
	}

	if (!(g_pDebugOverlay = (IVDebugOverlay *)factory(VDEBUG_OVERLAY_INTERFACE_VERSION, nullptr)))
	{
		Warning("[VR] Failed to find IVDebugOverlay\n");
		return false;
	}
	
	if(!(g_pLauncherMgr = (ILauncherMgr*)factory(SDLMGR_INTERFACE_VERSION, nullptr)))
	{
		Warning("[VR] Could not get %s\n", SDLMGR_INTERFACE_VERSION);
		return false;
	}

	return true;
}

static void TextureCreateHook(CGLMTex* tex)
{
	if(!tex->m_debugLabel)
		return;
	if(!V_strcmp(tex->m_debugLabel, "_rt_vr_left"))
	{
		gClientVR.m_texVrLeft = tex;
		Msg("[VR] Got _rt_vr_left: w=%u h=%u\n", tex->m_layout->m_slices[0].m_xSize,
			tex->m_layout->m_slices[0].m_ySize);
	}
	else if(!V_strcmp(tex->m_debugLabel, "_rt_vr_right"))
	{
		gClientVR.m_texVrRight = tex;
		Msg("[VR] Got _rt_vr_right: w=%u h=%u\n", tex->m_layout->m_slices[0].m_xSize,
			tex->m_layout->m_slices[0].m_ySize);
	}
}

void CSourceVR::Disconnect()
{
	BaseClass::Disconnect();
}

#define VR_ERROR (CommandLine()->CheckParm("-vr") ? INIT_FAILED : INIT_OK)

InitReturnVal_t CSourceVR::Init()
{
	BaseClass::Init();
	return INIT_OK;
	/* To obtain the backing renderbuffers/textures, we need to hook the create tex function, so let's do that now */
	int hook = HookTextureCreate(TextureCreateHook);
	
	/* First let's create the render targets for the left and right eye */
	m_vrLeft = g_pMaterialSystem->CreateNamedRenderTargetTexture("_rt_vr_left", 0, 0, RenderTargetSizeMode_t::RT_SIZE_DEFAULT, ImageFormat::IMAGE_FORMAT_RGBA8888);
	m_vrRight = g_pMaterialSystem->CreateNamedRenderTargetTexture("_rt_vr_right", 0, 0, RenderTargetSizeMode_t::RT_SIZE_DEFAULT, ImageFormat::IMAGE_FORMAT_RGBA8888);
		
	/* Explicitly disable VR */
	if (CommandLine()->CheckParm("-novr"))
	{
		Warning("VR disabled!\n");
		return INIT_OK;
	}
	
	if (!m_vrLeft || !m_vrRight)
	{
		Warning("Failed to create _rt_vr_left and/or _rt_vr_right!\n");

		return VR_ERROR;
	}

	vr::EVRInitError error;
	m_vrSystem = vr::VR_Init(&error, vr::EVRApplicationType::VRApplication_Scene);
	
	if(error != vr::VRInitError_None)
	{
		Warning("Failed to init openvr: %s\n", vr::VR_GetVRInitErrorAsEnglishDescription(error));
		//return VR_ERROR;
	}
	
	m_gameWindow = (SDL_Window*)g_pLauncherMgr->GetWindowRef();
	m_glContext = (SDL_GLContext)g_pLauncherMgr->GetGLContextForWindow(m_gameWindow);
	
	if(CommandLine()->CheckParm("-vrdebug") || true)
	{
		m_debugWindow = SDL_CreateWindow("SourceVR Debug Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			500, 500, SDL_WINDOW_OPENGL);
		m_debugContext = SDL_GL_CreateContext(m_debugWindow);
		
		/* Clear out the window */
		SDL_GL_MakeCurrent(m_debugWindow, m_debugContext);
		
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(m_debugWindow);
		
		/* Restore */
		SDL_GL_MakeCurrent(m_gameWindow, (SDL_GLContext)m_glContext);
	}
	
	return INIT_OK;
}

void CSourceVR::Shutdown()
{
	BaseClass::Shutdown();
}

IVRHooks *CSourceVR::GetHooks()
{
	static CVRClientHooks *clientHooks = new CVRClientHooks(this);
	return clientHooks;
}

void CSourceVR::GetViewportBounds(EVRView view, int &x, int &y, int &w, int &h)
{
	x = y = w = h = 0;
}

//=================================================================================================================//

/* Client only hooks. Not called on server */
void CVRClientHooks::PreRender()
{
}

void CVRClientHooks::Update(float frametime)
{
}

void CVRClientHooks::PostRender()
{	
}

void CVRClientHooks::Draw(EVRView eye)
{
	CMatRenderContextPtr render(g_pMaterialSystem);
	if (eye == EVRView::LEFT)
		render->SetRenderTarget(m_vr->m_vrLeft);
	else
		render->SetRenderTarget(m_vr->m_vrRight);
	render.SafeRelease();
}

/* Server only hooks. Not called on client */
void CVRClientHooks::FrameUpdatePreEntityThink()
{
}

void CVRClientHooks::FrameUpdatePostEntityThink()
{
}

void CVRClientHooks::PreClientUpdate()
{
}

/* Called on both client and server */
void CVRClientHooks::OnSave()
{
}

void CVRClientHooks::OnRestore()
{
}

void CVRClientHooks::LevelInitPreEntity()
{
}

void CVRClientHooks::LevelInitPostEntity()
{
}

void CVRClientHooks::LevelShutdownPreEntity()
{
}

void CVRClientHooks::LevelShutdownPostEntity()
{
}
