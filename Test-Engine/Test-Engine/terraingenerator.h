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
	Texture * mTexture;
	unsigned int mVertexCount;

	Terrain() :
		mVAO(nullptr), mVertexCount(0), mTexture(nullptr){}

	Terrain(VertexArray * pVAO, Texture * pTex, unsigned int pVertexCount) :
		mVAO(pVAO), mVertexCount(pVertexCount), mTexture(pTex) {}
};

class TerrainGenerator {
public:
	static Terrain createTerrain(unsigned int pVertexCount, unsigned int pSize, float pAmplitude, std::string pHmName, std::string pTexture);
private:
	static glm::vec3 calculateNormal(int x, int y, HeightsGenerator * pHeightsGenerator);
	static float getHeight(int x, int y, HeightsGenerator * pHeightsGenerator);

	static glm::vec3 calculateNormal(int x, int y, HeightmapLoader * pHmLoader);
	static float getHeight(int x, int y, HeightmapLoader * pHmLoader);

	static glm::vec3 generateColor(float height);
};

