/*
 * physics_record.h
 *
 * Physics state recording and playback
 *
 */
#pragma once
#include "cbase.h"
#include "coordsize.h"
#include "entitylist.h"
#include "vcollide_parse.h"
#include "soundenvelope.h"
#include "game.h"
#include "utlvector.h"
#include "init_factory.h"
#include "igamesystem.h"
#include "hierarchy.h"
#include "IEffects.h"
#include "engine/IEngineSound.h"
#include "world.h"
#include "decals.h"
#include "physics_fx.h"
#include "vphysics/vehicles.h"
#include "vehicle_sounds.h"
#include "movevars_shared.h"
#include "physics_saverestore.h"
#include "solidsetdefaults.h"
#include "tier0/vprof.h"
#include "engine/IStaticPropMgr.h"
#include "physics_prop_ragdoll.h"
#include <vphysics_interface.h>
#include <vphysics_interfaceV30.h>
#include <physics.h>
#include <baseentity.h>
#include <physics_fx.h>
#include <tier1/utlvector.h>

//==================================================================================//
// Random physics utilities
//      - Allows you to add custom physics events
//==================================================================================//
namespace physutl
{
	void RegisterEventHandler(IPhysicsCollisionEvent* pevh);
	void RegisterEventHandler(IPhysicsObjectEvent* pevh);
}

//==================================================================================//
// CPhysicsEventProxy
//      - Catches physics events and relays them to our physics recording system
//==================================================================================//
class CPhysicsEventProxy : public IPhysicsCollisionEvent, IPhysicsObjectEvent
{
public:
	CPhysicsEventProxy();

	/* IPhysicsCollisionEvent */
	void PreCollision( vcollisionevent_t *pEvent ) override; //
	void PostCollision( vcollisionevent_t *pEvent ) override; //
	void Friction( IPhysicsObject *pObject, float energy, int surfaceProps, int surfacePropsHit, IPhysicsCollisionData *pData ) override; //
	void StartTouch( IPhysicsObject *pObject1, IPhysicsObject *pObject2, IPhysicsCollisionData *pTouchData ) override; //
	void EndTouch( IPhysicsObject *pObject1, IPhysicsObject *pObject2, IPhysicsCollisionData *pTouchData ) override; //
	void FluidStartTouch( IPhysicsObject *pObject, IPhysicsFluidController *pFluid ) override; //
	void FluidEndTouch( IPhysicsObject *pObject, IPhysicsFluidController *pFluid ) override; //
	void PostSimulationFrame() override; //
	void ObjectEnterTrigger( IPhysicsObject *pTrigger, IPhysicsObject *pObject ) override; //
	void ObjectLeaveTrigger( IPhysicsObject *pTrigger, IPhysicsObject *pObject ) override; //

	/* IPhysicsObjectEvent */
	void ObjectWake( IPhysicsObject *pObject ) override;
	void ObjectSleep( IPhysicsObject *pObject ) override;

public:
	CUtlVector<IPhysicsCollisionEvent*>     m_CollisionEventHandlers;
	CUtlVector<IPhysicsObjectEvent*>        m_ObjectEventHandlers;
};

class CEntityState
{

};

class CPhysicsState
{
protected:
};