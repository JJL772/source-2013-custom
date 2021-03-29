
#include "vr_shared_support.h"

#ifdef CLIENT_DLL
#include "cdll_client_int.h"
#endif 

class CVRGameSystem : public CAutoGameSystemPerFrame
{
	IVRHooks* m_hooks;
public:
	CVRGameSystem(IVRHooks* hooks)
	{
		m_hooks = hooks;
	}
	
#ifdef CLIENT_DLL
	// Called before rendering
	void PreRender() override
	{
		m_hooks->PreRender();
	}

	// Gets called each frame
	void Update( float frametime ) override
	{
		m_hooks->Update(frametime);
	}

	void PostRender() override
	{
		m_hooks->PostRender();
	}
#else
	// Called each frame before entities think
	void FrameUpdatePreEntityThink() override
	{
		m_hooks->FrameUpdatePreEntityThink();
	}
	
	// called after entities think
	void FrameUpdatePostEntityThink() override
	{
		m_hooks->FrameUpdatePostEntityThink();
	}
	
	void PreClientUpdate() override
	{
		m_hooks->PreClientUpdate();
	}
#endif

	void OnSave() override
	{
		m_hooks->OnSave();
	}
	
	void OnRestore() override
	{
		m_hooks->OnRestore();
	}
	
	void LevelInitPreEntity() override
	{
		m_hooks->LevelInitPreEntity();
	}
	
	void LevelInitPostEntity() override
	{
		m_hooks->LevelInitPostEntity();
	}
	
	void LevelShutdownPreEntity() override
	{
		m_hooks->LevelShutdownPreEntity();
	}
	
	void LevelShutdownPostEntity() override
	{
		m_hooks->LevelShutdownPostEntity();
	}
};


IGameSystem* GetVRGameSystem(IVRHooks* hooks)
{
	static CVRGameSystem* gameSys = new CVRGameSystem(hooks);
	return gameSys;
}

bool ShouldUseVR()
{
	static ConVarRef vr_enable("vr_enable");
#ifdef CLIENT_DLL
	return g_pVR != nullptr && vr_enable.GetBool();
#else
	return false;
#endif 
}