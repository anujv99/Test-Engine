#pragma once

#include <string>
#include <fstream>
#include <ios>

#include "vertexarray.h"

struct ToxicModel {
	VertexArray * mVAO;
	unsigned int mVertexCount;
	ToxicModel() :
		mVAO(nullptr), mVertexCount(-1) {}
	ToxicModel(VertexArray * pVAO, unsigned int pVertexCount) :
		mVAO(pVAO), mVertexCount(pVertexCount) {}
};

class BasicLoader {
public:
	static bool loadModel(std::string pFilePath);
};
