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

#include "vr/vr.h"

IVDebugOverlay* g_pDebugOverlay = nullptr;


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
	IVRHooks* GetHooks() override;

public:
	ITexture *m_vrRight;
	ITexture *m_vrLeft;

	/* OpenVR properties */
	vr::IVRSystem* m_vrSystem;
	
};

class CVRClientHooks : public IVRHooks
{
public:
	/* Client only hooks. Not called on server */
	void PreRender() override;
	void Update( float frametime ) override;
	void PostRender() override;
	void Draw(IVRenderView* rv) override;
	
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

EXPOSE_SINGLE_INTERFACE(CSourceVR, IVRClient, VRCLIENT_MODULE_VERSION);

//=================================================================================================================//

bool CSourceVR::Connect(CreateInterfaceFn factory)
{
	BaseClass::Connect(factory);

	DevMsg("Connected vr.so\n");
	
	if(!g_pMaterialSystem)
	{
		Warning("g_pMaterialSystem was null\n");
		return false;
	}
	
	if(!(g_pDebugOverlay = (IVDebugOverlay*)factory(VDEBUG_OVERLAY_INTERFACE_VERSION, nullptr)))
	{
		Warning("Failed to find IVDebugOverlay");
		return false;
	}
	
	return true;
}

void CSourceVR::Disconnect()
{
	BaseClass::Disconnect();
}

#define VR_ERROR (CommandLine()->CheckParm("-vr") ? INIT_FAILED : INIT_OK)
#define FAILED(x) (x != XR_SUCCESS)

InitReturnVal_t CSourceVR::Init()
{
	BaseClass::Init();
	
	/* First let's create the render targets for the left and right eye */
	m_vrLeft = g_pMaterialSystem->CreateNamedRenderTargetTexture("_rt_vr_left", 0, 0, RenderTargetSizeMode_t::RT_SIZE_DEFAULT, ImageFormat::IMAGE_FORMAT_RGBA8888);
	m_vrRight = g_pMaterialSystem->CreateNamedRenderTargetTexture("_rt_vr_right", 0, 0, RenderTargetSizeMode_t::RT_SIZE_DEFAULT, ImageFormat::IMAGE_FORMAT_RGBA8888);
	
	/* Explicitly disable VR */
	if (CommandLine()->CheckParm("-novr"))
		return INIT_OK;

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
		return VR_ERROR;
	}
	

	return INIT_OK;
}

void CSourceVR::Shutdown()
{
	BaseClass::Shutdown();
}

IVRHooks* CSourceVR::GetHooks()
{
	static CVRClientHooks* clientHooks = new CVRClientHooks();
	return clientHooks;
}

//=================================================================================================================//

/* Client only hooks. Not called on server */
void CVRClientHooks::PreRender() 
{
	
}

void CVRClientHooks::Update( float frametime ) 
{
	
}

void CVRClientHooks::PostRender() 
{
	
}

void CVRClientHooks::Draw(IVRenderView* rv)
{
	
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
