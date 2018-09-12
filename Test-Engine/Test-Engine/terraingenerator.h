#pragma once

#include <algorithm>
#include <vector>
#include <string>

#include "openglresources.h"
#include "heightsgenerator.h"
#include "heightmaploader.h"

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
	static Terrain createTerrain(unsigned int pVertexCount, unsigned int pSize, std::string pHmName);
private:
	static glm::vec3 calculateNormal(int x, int y, HeightsGenerator * pHeightsGenerator);
	static float getHeight(int x, int y, HeightsGenerator * pHeightsGenerator);

	static glm::vec3 calculateNormal(int x, int y, HeightmapLoader * pHmLoader);
	static float getHeight(int x, int y, HeightmapLoader * pHmLoader);

	static glm::vec3 generateColor(float height);
};

