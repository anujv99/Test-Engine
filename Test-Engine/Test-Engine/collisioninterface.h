#pragma once

#include "collisionworld.h"

class CollisionInterface {
public:
	static void start() { mWorld->startThread(); }
	static void stop() { mWorld->endThread(); }
	static void createCollisionWorld();
	static void cleanUP();
	static void update() { mWorld->update(); }
	static void setWorld(CollisionWorld * pWorld) { mWorld = pWorld; }
	static void setGravity(glm::vec3 pGravity);
	static void addTerrainCollidor(Terrain * pTerrain);
	static RigidBodyStructure * createRigidBody(glm::vec3 pPosition = glm::vec3(0), glm::vec3 pRotation = glm::vec3(0), float pScale = 1.0f, float pMass = 0.0f);
private:
	static CollisionWorld * mWorld;
};

