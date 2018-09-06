#pragma once

#include "openglresources.h"

#include <GLM/glm.hpp>

struct Terrain {
	VertexArray * mVAO;
	unsigned  int mVertexCount;

	Terrain() :
		mVAO(nullptr), mVertexCount(0) {}

	Terrain(VertexArray * pVAO, unsigned int pVertexCount) :
		mVAO(pVAO), mVertexCount(pVertexCount) {}

};

class TerrainGenerator {
public:
	static Terrain createTerrain(unsigned int pVertexCount, unsigned int pSize);
private:
};

