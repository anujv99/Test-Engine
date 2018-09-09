#pragma once

#include "openglresources.h"

struct Water {
	VertexArray * mVAO;
	unsigned int mVertexCount;
	float mHeight;

	Water() :
		mVAO(nullptr), mVertexCount(0), mHeight(0) {
	}

	Water(VertexArray * pVAO, unsigned int pVertexCount, float pHeight) :
		mVAO(pVAO), mVertexCount(pVertexCount), mHeight(pHeight) {
	}

};

class WaterGenerator {
public:
	static Water addWater(unsigned int pVertexCount, unsigned int pSize);
};

