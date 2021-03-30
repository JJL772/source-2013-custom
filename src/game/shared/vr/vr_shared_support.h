//===========================================================================//
// Purpose: Support code for VR module
//===========================================================================//

#pragma once

#include "tier0/basetypes.h"
#include "igamesystem.h"
#include "vr/vr.h"

IGameSystem* GetVRGameSystem(IVRHooks* hooks);
bool ShouldUseVR();
IVRHooks* GetVRHooks();