#pragma once

#include "terraingenerator.h"
#include "basicloader.h"

#define GRAVITY 1.0f / 60.0f

class Player {
public:
	static void setPlayer(Model * pPlayer, Terrain * pTerrain);
	static void update();
private:
	static Model * mPlayer;
	static Terrain * mTerrain;
	static glm::vec3 mVelocity;
};

