#pragma once

#include "openglresources.h"

struct Water {
	VertexArray * mVAO;
	unsigned int mVertexCount;

	Water() :
		mVAO(nullptr), mVertexCount(0) {
	}

	Water(VertexArray * pVAO, unsigned int pVertexCount) :
		mVAO(pVAO), mVertexCount(pVertexCount) {
	}

};

class WaterGenerator {
public:
	static Water addWater(unsigned int pVertexCount, unsigned int pSize);
};

