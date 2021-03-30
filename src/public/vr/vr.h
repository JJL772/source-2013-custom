// VR module prototypes

#pragma once

#include "appframework/IAppSystem.h"
#include "materialsystem/imaterialsystem.h"
#include "ivrenderview.h"

#define VRCLIENT_MODULE_VERSION "IVRClient001"
#define VRSERVER_MODULE_VERSION "IVRServer001"

enum class EVRView
{
	LEFT = 0,
	RIGHT
};

class IVRHooks
{
public:
	/* Client only hooks. Not called on server */
	virtual void PreRender() = 0;
	virtual void Update( float frametime ) = 0;
	virtual void PostRender() = 0;
	
	/* Server only hooks. Not called on client */
	virtual void FrameUpdatePreEntityThink() = 0;
	virtual void FrameUpdatePostEntityThink() = 0;
	virtual void PreClientUpdate() = 0;
	
	/* Called on both client and server */
	virtual void OnSave() = 0;
	virtual void OnRestore() = 0;
	virtual void LevelInitPreEntity() = 0;
	virtual void LevelInitPostEntity() = 0;
	virtual void LevelShutdownPreEntity() = 0;
	virtual void LevelShutdownPostEntity() = 0;
	
	/* Additional events for the client */
	virtual void Draw(EVRView view) = 0;
	
};

//==========================================//
// Purpose: Client interface to VR module
//==========================================//
class IVRClient
{
public:
	virtual IVRHooks* GetHooks() = 0;
	virtual void GetViewportBounds(EVRView view, int& x, int& y, int& w, int& h) = 0;
};

//==========================================//
// Purpose: Server interface to VR module
//==========================================//
class IVRServer
{
public:
	virtual IVRHooks* GetHooks() = 0;
};