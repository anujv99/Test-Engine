#pragma once

#include <GLM/glm.hpp>

#include <glad/glad.h>

#include "openglresources.h"

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
};

