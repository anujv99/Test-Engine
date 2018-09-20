#include "terraincollision.h"

float TerrainCollision::getHeight(float x, float y) {
	if (mTerrain == nullptr) {
		printf("COLLISION::Set terrain first!\n");
		return -1;
	}
	return mTerrain->getHeightOfTerrain(x, y);
}

float TerrainCollision::getHeight(glm::vec3 pPos) {
	if (mTerrain == nullptr) {
		printf("COLLISION::Set terrain first!\n");
		return -1;
	}
	return mTerrain->getHeightOfTerrain(pPos.x, pPos.z);
}

void TerrainCollision::checkCollision(RigidBodyStructure * pRigidBody, bool pShouldRespond) {
	auto pos = pRigidBody->getPosition();
	auto height = getHeight(pos);
	if (pos.y < height) {
		if (pShouldRespond) {
			pRigidBody->setPosition(glm::vec3(pos.x, height, pos.z));
			pRigidBody->getVelocity()->y = 0;
		}
	}
}
