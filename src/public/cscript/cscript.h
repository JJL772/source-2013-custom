#pragma once

#include "appframework/IAppSystem.h"
#include "tier2/tier2.h"
#include "igameevents.h"

using ScriptModule_t = int;

static constexpr ScriptModule_t INVALID_SCRIPT_MODULE = -1;

#define CSCRIPT_INTERFACE_VERSION "ICScript001"

class ICScript
{
public:
	virtual ScriptModule_t LoadModule(const char* module) = 0;
	
	virtual void UnloadModule(ScriptModule_t mod) = 0;
	
	virtual void InvokeGameEvent(IGameEvent* event) = 0;
	
	virtual void OnFrame(float dt) = 0;
	
	virtual void OnSave() = 0;
	
	virtual void OnRestore() = 0;
	
	virtual void OnLevelInit(bool pre_entity) = 0;
	
	virtual void OnLevelShutdown(bool post_entity) = 0;
	
	virtual void PreRender() = 0;
	
	virtual void PostRender() = 0;
	
	virtual void PreClientUpdate() = 0;
};