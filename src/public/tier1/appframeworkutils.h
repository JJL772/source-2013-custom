#pragma once 

#include "interface.h"
#include "appframework/AppFramework.h"
#include "tier0/platform.h"
#include "tier2/tier2.h"
#include "appframework/IAppSystem.h"

//-----------------------------------------------------------------------------
// Called to load an interface from the specified DLL and calls Connect on it
//-----------------------------------------------------------------------------
template<class T>
T* LoadInterface(const char* module_name, const char* interface_name, CreateInterfaceFn factory)
{
	char cwd[MAX_PATH];
	_getcwd(cwd, MAX_PATH);
	
	const char* game = nullptr;
	CommandLine()->CheckParm("-game", &game);
	game = game ? game : "hl2";
	
	/* No extension, so we should build a DLL name */
	char modname[MAX_PATH];
	if(!V_strstr(module_name, ".")) {
		V_snprintf(modname, sizeof(modname), "%s/%s/bin/%s%s", cwd, game, module_name, DLL_EXT_STRING);
	}
	else
		V_snprintf(modname, sizeof(modname), "%s/%s/bin/%s", cwd, game, modname);
		//V_strncpy(modname, module_name, sizeof(modname));
		
	Msg("Loading %s\n", modname);
		
	/* NOTE: intentionally not freeing the module because it needs to exist for the lifetime of the app */
	CSysModule* hDLL = Sys_LoadModule(modname);
	if(!hDLL)
		return nullptr;
		
	CreateInterfaceFn hFactory = Sys_GetFactory(hDLL);
	if(!hFactory)
		return nullptr;
	
	int ret;
	T* pInterface = nullptr;
	pInterface = (T*)hFactory(interface_name, &ret);
	
	CBaseAppSystem<T>* appsys = (CBaseAppSystem<T>*)pInterface;
	appsys->Connect(factory);
	
	return pInterface;
}

template<class T>
int InitInterface(T* iface)
{
	CBaseAppSystem<T>* appsys = (CBaseAppSystem<T>*)iface;
	return appsys->Init();
}