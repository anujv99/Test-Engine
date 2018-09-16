#pragma once

#include "openglresources.h"

struct Grass {
	VertexArray * mVAO;
	unsigned int mVertexCount;
	Texture * mTex;

	Grass() :
		mVAO(nullptr), mVertexCount(0), mTex(nullptr) {}
	Grass(VertexArray * pVAO, unsigned int pVertexCount, Texture * pTex) :
		mVAO(pVAO), mVertexCount(pVertexCount), mTex(pTex) {}

};

class GrassLoader {
public:
	static Grass generateGrass();
private:
	static bool isModelGenerated;
	static VertexArray * mVAO;
	static unsigned int mVertexCount;
};

