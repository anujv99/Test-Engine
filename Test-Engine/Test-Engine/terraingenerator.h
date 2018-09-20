#pragma once

#include <string>

#include "openglresources.h"
#include "heightsgenerator.h"
#include "heightmaploader.h"

#include <GLM/glm.hpp>

struct Terrain {
	VertexArray * mVAO;
	Texture * mTexture;
	unsigned int mVertexCount;
	int mDivisions;
	unsigned int mSize;

	Terrain() :
		mVAO(nullptr), mVertexCount(0), mTexture(nullptr) {
	}

	Terrain(VertexArray * pVAO, Texture * pTex, unsigned int pVertexCount) :
		mVAO(pVAO), mVertexCount(pVertexCount), mTexture(pTex) {
	}
public:
	void clean() {
		for (int i = 0; i < mDivisions; i++) {
			delete[] mHeights[i];
		}
		delete[] mHeights;
	}
	void setHeight(float ** pHeights) {
		mHeights = pHeights;
	}
	float getHeightOfTerrain(float x, float y) {
		float gridSquareSize = mSize / (float)(mDivisions - 1);
		int griX = (int)std::floor(x / gridSquareSize);
		int griY = (int)std::floor(y / gridSquareSize);
		if (griX >= mDivisions - 1 || griY >= mDivisions - 1 || griX < 0 || griY < 0) {
			return -100000.0f;
		}
		float xCoord = fmod(x, gridSquareSize) / gridSquareSize;
		float yCoord = fmod(y, gridSquareSize) / gridSquareSize;
		float answer = 0;
		if (xCoord <= (1 - yCoord)) {
			answer = barryCentric(glm::vec3(0, mHeights[griX][griY], 0), glm::vec3(1,
				mHeights[griX + 1][griY], 0), glm::vec3(0,
					mHeights[griX][griY + 1], 1), glm::vec2(xCoord, yCoord));
		} else {
			answer = barryCentric(glm::vec3(1, mHeights[griX + 1][griY], 0), glm::vec3(1,
				mHeights[griX + 1][griY + 1], 1), glm::vec3(0,
					mHeights[griX][griY + 1], 1), glm::vec2(xCoord, yCoord));
		}
		return answer;
	}
private:
	float ** mHeights;
	float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}
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

