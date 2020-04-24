/*
 *
 * physics_record.cpp
 *
 * Implementation of Physics state recording and playback
 *
 */
#include "physics_record.h"
#include "physics_collisionevent.h"

/* Should probably expose this in headers somewhere */
extern CCollisionEvent g_Collisions;

/* Convars */
//ConVar sv_phys_show_collisions("sv_phys_show_collisions", "0", FCVAR_CHEAT | FCVAR_ARCHIVE, "Shows points where things collide");

CPhysicsEventProxy::CPhysicsEventProxy()
{

}

void CPhysicsEventProxy::PreCollision(vcollisionevent_t *pEvent)
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->PostCollision(pEvent);
}

void CPhysicsEventProxy::PostCollision(vcollisionevent_t *pEvent)
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->PostCollision(pEvent);
}

void CPhysicsEventProxy::Friction(IPhysicsObject *pObject, float energy, int surfaceProps, int surfacePropsHit,
                                  IPhysicsCollisionData *pData)
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->Friction(pObject, energy, surfaceProps, surfacePropsHit, pData);
}

void CPhysicsEventProxy::StartTouch(IPhysicsObject *pObject1, IPhysicsObject *pObject2, IPhysicsCollisionData *pTouchData)
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->StartTouch(pObject1, pObject2, pTouchData);
}

void CPhysicsEventProxy::EndTouch(IPhysicsObject *pObject1, IPhysicsObject *pObject2, IPhysicsCollisionData *pTouchData)
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->EndTouch(pObject1, pObject2, pTouchData);
}

void CPhysicsEventProxy::FluidStartTouch(IPhysicsObject *pObject, IPhysicsFluidController *pFluid)
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->FluidStartTouch(pObject, pFluid);
}

void CPhysicsEventProxy::FluidEndTouch(IPhysicsObject *pObject, IPhysicsFluidController *pFluid)
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->FluidEndTouch(pObject, pFluid);
}

void CPhysicsEventProxy::PostSimulationFrame()
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->PostSimulationFrame();
}

void CPhysicsEventProxy::ObjectEnterTrigger(IPhysicsObject *pTrigger, IPhysicsObject *pObject)
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->ObjectEnterTrigger(pTrigger, pObject);

}

void CPhysicsEventProxy::ObjectLeaveTrigger(IPhysicsObject *pTrigger, IPhysicsObject *pObject)
{
	for(auto handler : this->m_CollisionEventHandlers)
		handler->ObjectLeaveTrigger(pTrigger, pObject);
}

void CPhysicsEventProxy::ObjectWake(IPhysicsObject *pObject)
{
	for(auto handler : this->m_ObjectEventHandlers)
		handler->ObjectWake(pObject);
}

void CPhysicsEventProxy::ObjectSleep(IPhysicsObject *pObject)
{
	for(auto handler : this->m_ObjectEventHandlers)
		handler->ObjectWake(pObject);
}