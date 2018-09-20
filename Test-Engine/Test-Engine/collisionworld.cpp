#include "collisionworld.h"

CollisionWorld::CollisionWorld() {}

CollisionWorld::~CollisionWorld() {
	for (auto collidor : mTerrains) {
		delete(collidor);
	}
	for (auto collidor : mRigidBodies) {
		delete(collidor);
	}
}

void CollisionWorld::update() {
	updateRigidBodies();
	checkTerrainCollision();
}

void CollisionWorld::addTerrainCollidor(Terrain * pTerrain) {
	auto tTerr = new TerrainCollision(pTerrain);
	mTerrains.push_back(tTerr);
}

RigidBodyStructure * CollisionWorld::createRigidBody(glm::vec3 pPosition, glm::vec3 pRotation, float pScale, float pMass) {
	auto tRigibBody = new RigidBodyStructure(pPosition, pRotation, pScale, pMass);
	mRigidBodies.push_back(tRigibBody);
	return mRigidBodies.back();
}

void CollisionWorld::checkTerrainCollision() {
	for (auto terr : mTerrains) {
		for (RigidBodyStructure * rigidBody : mRigidBodies) {
			terr->checkCollision(rigidBody);
		}
	}
}

void CollisionWorld::updateRigidBodies() {
	for (auto rigidboy : mRigidBodies) {
		rigidboy->accelerate(mGravity);
		rigidboy->update();
	}
}
