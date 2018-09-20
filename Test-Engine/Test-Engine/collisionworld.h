#pragma once

#include <list>
#include "rigidbodystructure.h"
#include "terraincollision.h"

class CollisionWorld {
public:
	CollisionWorld();
	~CollisionWorld();
	void update();
public:
	bool getThreadStatus() { return isThreadFinished; }
	void startThread();
	void endThread();
	void setGravity(glm::vec3 &pGravity) { mGravity = pGravity / 100.0f; }
	void addTerrainCollidor(Terrain * pTerrain);
	RigidBodyStructure * createRigidBody(glm::vec3 pPosition = glm::vec3(0), glm::vec3 pRotation = glm::vec3(0), float pScale = 1.0f, float pMass = 1.0f);
private:
	void checkTerrainCollision();
	void updateRigidBodies();
	void delay(double timeInMillis);
private:
	std::list<RigidBodyStructure*> mRigidBodies;
	std::list<TerrainCollision*> mTerrains;
	glm::vec3 mGravity = glm::vec3(0, 0, 0);
	bool isActive = false;
	bool isThreadFinished = false;
};
