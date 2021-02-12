#include "cscript/cscript.h"

#include "appframework/AppFramework.h"
#include "appframework/IAppSystem.h"

class CScript : public CTier2AppSystem<ICScript>
{
public:
	/* IAppSystem */
	virtual bool Connect( CreateInterfaceFn factory ) override;
	virtual void Disconnect() override;
	virtual InitReturnVal_t Init() override;
	virtual void Shutdown() override;
	
	/* ICScript */
	virtual ScriptModule_t LoadModule(const char* module) override;
	
	virtual void UnloadModule(ScriptModule_t mod) override;
	
	virtual void InvokeGameEvent(IGameEvent* event) override;
	
	virtual void OnFrame(float dt) override;
	
	virtual void OnSave() override;
	
	virtual void OnRestore() override;
	
	virtual void OnLevelInit(bool pre_entity) override;
	
	virtual void OnLevelShutdown(bool post_entity) override;
	
	virtual void PreRender() override;
	
	virtual void PostRender() override;
	
	virtual void PreClientUpdate() override;
};

EXPOSE_SINGLE_INTERFACE(CScript, ICScript, CSCRIPT_INTERFACE_VERSION);

bool CScript::Connect( CreateInterfaceFn factory )
{
	ConnectTier1Libraries(&factory, 1);
	ConnectTier2Libraries(&factory, 1);
	return true;
}

void CScript::Disconnect()
{
	DisconnectTier1Libraries();
	DisconnectTier2Libraries();
}

InitReturnVal_t CScript::Init() 
{
	return INIT_OK;
}

void CScript::Shutdown() 
{
	
}

ScriptModule_t CScript::LoadModule(const char* module)
{
	return INVALID_SCRIPT_MODULE;
}

void CScript::UnloadModule(ScriptModule_t mod) 
{
	
}

void CScript::InvokeGameEvent(IGameEvent* event) 
{
	
}

void CScript::OnFrame(float dt) 
{
	
}

void CScript::OnSave() 
{
	
}

void CScript::OnRestore() 
{
	
}

void CScript::OnLevelInit(bool pre_entity) 
{
	
}

void CScript::OnLevelShutdown(bool post_entity) 
{
	
}

void CScript::PreRender() 
{
	
}

void CScript::PostRender() 
{
	
}

void CScript::PreClientUpdate() 
{
	
}
