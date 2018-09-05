#pragma once

#include <string>
#include <fstream>
#include <ios>
#include <vector>

#include <GLM/glm.hpp>

#include "stb_image.h"
#include "openglresources.h"

struct Model {
	VertexArray * mVAO;
	Texture * mDiffuseTex;
	unsigned int mVertexCount;
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	float mScale;
	Model() :
		mVAO(nullptr), mVertexCount(-1) {
	}
	Model(VertexArray * pVAO, unsigned int pVertexCount) :
		mVAO(pVAO), mVertexCount(pVertexCount), mPosition(glm::vec3(0)), mRotation(glm::vec3(0)), mScale(1) {
	}
};

class BasicLoader {
public:
	static Model loadModel(std::string pFilePath);
private:
	static int readINT(std::ifstream * pInFile);
	static void readBuffer(std::ifstream * pInFile, void * pStream, unsigned int pBufferSize);
};
