#include "StdAfx.h"

#include "CPlayerController.h"
#include "CPhysicsObject.h"
#include "convert.h"

CPlayerController::CPlayerController(CPhysicsObject* pObject) {
	m_pObject = pObject;
}

CPlayerController::~CPlayerController() {

}

void CPlayerController::Update(const Vector& position, const Vector& velocity, float secondsToArrival, bool onground, IPhysicsObject* ground) {
	btVector3 pos, vel;
	ConvertPosToBull(position, pos);
	ConvertPosToBull(velocity, vel);
	btRigidBody* object = m_pObject->GetObject();
	btTransform transform = object->getWorldTransform();
	transform.setOrigin(pos);
	object->setWorldTransform(transform);
	object->setInterpolationLinearVelocity(vel);	
}

void CPlayerController::SetEventHandler(IPhysicsPlayerControllerEvent* handler) {
	m_handler = handler;
}

bool CPlayerController::IsInContact() {
	NOT_IMPLEMENTED;
	return false;
}

void CPlayerController::MaxSpeed(const Vector& maxVelocity) {
	NOT_IMPLEMENTED;
}

void CPlayerController::SetObject(IPhysicsObject* pObject) {
	m_pObject = (CPhysicsObject*)pObject;
}

int CPlayerController::GetShadowPosition( Vector* position, QAngle* angles ) {
	btRigidBody* pObject = m_pObject->GetObject();
	btTransform transform = pObject->getWorldTransform();
	if (position) {
		btVector3 btvec = transform.getOrigin();
		ConvertPosToHL(btvec, *position);
	}
	if (angles) {
		btMatrix3x3 btmatrix = transform.getBasis();
		ConvertRotationToHL(btmatrix, *angles);
	}
	// FIXME: what is this?
	// Andrew; this needs to return the amount of ticks since the last Update()
	return 0;
}

void CPlayerController::StepUp(float height) {
	btVector3 step;
	ConvertPosToBull(Vector(0, 0, height), step);
	btRigidBody* pObject = m_pObject->GetObject();
	btTransform transform = pObject->getWorldTransform();
	transform.setOrigin(transform.getOrigin()+step);
}

void CPlayerController::Jump() {
	NOT_IMPLEMENTED;
}

void CPlayerController::GetShadowVelocity(Vector* velocity) {
	NOT_IMPLEMENTED;
}

IPhysicsObject* CPlayerController::GetObject() {
	NOT_IMPLEMENTED;
	return NULL;
}

void CPlayerController::GetLastImpulse(Vector* pOut) {
	NOT_IMPLEMENTED;
}

void CPlayerController::SetPushMassLimit(float maxPushMass) {
	m_PushMassLimit = maxPushMass;
}

void CPlayerController::SetPushSpeedLimit(float maxPushSpeed) {
	m_PushSpeedLimit = maxPushSpeed;
}

float CPlayerController::GetPushMassLimit() {
	return m_PushMassLimit;
}

float CPlayerController::GetPushSpeedLimit() {
	return m_PushSpeedLimit;
}

bool CPlayerController::WasFrozen() {
	NOT_IMPLEMENTED;
	return false;
}
