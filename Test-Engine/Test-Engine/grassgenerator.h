#pragma once

#include "openglresources.h"

struct Grass {
	VertexArray * mVAO;
	unsigned int mVertexCount;

	Grass() :
		mVAO(nullptr), mVertexCount(0) {}
	Grass(VertexArray * pVAO, unsigned int pVertexCount) :
		mVAO(pVAO), mVertexCount(pVertexCount) {}

};

class GrassGenerator {
public:
	static Grass generateGrass();
private:
	static bool isModelGenerated;
	static VertexArray * mVAO;
	static unsigned int mVertexCount;
};

