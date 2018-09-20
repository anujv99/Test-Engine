#pragma once

#include "terraingenerator.h"
#include "rigidbodystructure.h"

class TerrainCollision {
public:
	TerrainCollision(Terrain * pTerrain) { mTerrain = pTerrain; }
	float getHeight(float x, float y);
	float getHeight(glm::vec3 pPos);
	void checkCollision(RigidBodyStructure * pRigidBody, bool pShouldRespond = true);
private:
	Terrain * mTerrain;
};
