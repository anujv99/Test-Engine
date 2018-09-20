#include "collisioninterface.h"

CollisionWorld * CollisionInterface::mWorld = nullptr;

void CollisionInterface::createCollisionWorld() {
	mWorld = new CollisionWorld;
}

void CollisionInterface::cleanUP() {
	while (true) {
		if (mWorld->getThreadStatus() == true) {
			delete(mWorld);
			break;
		}
	}
}

void CollisionInterface::setGravity(glm::vec3 pGravity) {
	if (mWorld != nullptr) {
		mWorld->setGravity(pGravity);
	}
}

void CollisionInterface::addTerrainCollidor(Terrain * pTerrain) {
	if (mWorld != nullptr) {
		mWorld->addTerrainCollidor(pTerrain);
	}
}

RigidBodyStructure * CollisionInterface::createRigidBody(glm::vec3 pPosition, glm::vec3 pRotation, float pScale, float pMass) {
	if (mWorld != nullptr) {
		return mWorld->createRigidBody(pPosition, pRotation, pScale, pMass);
	} else {
		return nullptr;
	}
}
