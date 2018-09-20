#pragma once

#include <string>
#include <GLM/glm.hpp>
#include "openglresources.h"
#include "collisioninterface.h"

struct Model {
	VertexArray * mVAO;
	Texture * mDiffuseTex;
	unsigned int mVertexCount;
	RigidBodyStructure * mRigidBody;

	Model() :
		mVAO(nullptr), mVertexCount(-1) {}
	Model(VertexArray * pVAO, unsigned int pVertexCount) :
		mVAO(pVAO), mVertexCount(pVertexCount), mRigidBody(nullptr) {}
};

class BasicLoader {
public:
	static Model loadModel(std::string pFilePath);
private:
	static int readINT(std::ifstream * pInFile);
	static void readBuffer(std::ifstream * pInFile, void * pStream, unsigned int pBufferSize);
};
