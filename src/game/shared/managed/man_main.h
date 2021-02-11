#pragma once

#include "tier0/basetypes.h"
#include "igameevents.h"
#include "igamesystem.h"
#include "convar.h"

class CManagedModule;

class CManagedScriptSystem
{
public:
	CManagedModule* LoadModule(const char* module);
	
	void UnloadModule(CManagedModule* module);
};

CManagedScriptSystem& GlobalScriptSystem();

class CManagedGameSystem : public CAutoGameSystemPerFrame
{
public:
	CManagedGameSystem();
	
	bool Init() override;
	void PostInit() override;
	void Shutdown() override;

	void LevelInitPreEntity() override;
	void LevelInitPostEntity() override;
	void LevelShutdownPreClearSteamAPIContext() override;
	void LevelShutdownPreEntity() override;
	void LevelShutdownPostEntity() override;

	void OnSave() override;
	void OnRestore() override;
	void SafeRemoveIfDesired() override;
};