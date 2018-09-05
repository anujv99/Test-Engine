#pragma once

#include <string>
#include <fstream>
#include <ios>
#include <list>
#include <vector>

#include "vertexarray.h"
#include <GLM/glm.hpp>

struct Model {
	VertexArray * mVAO;
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
	static void cleanUP();
private:
	static int readINT(std::ifstream * pInFile);
	static void readBuffer(std::ifstream * pInFile, void * pStream, unsigned int pBufferSize);
	static VertexArray * createVAO();
	static VertexBuffer * createVBO(const float * pData, unsigned int pSize);
	static IndexBuffer * createIBO(const int * pData, unsigned int pSize);
private:
	static std::list<VertexArray> mVaos;
	static std::list<VertexBuffer> mVbos;
	static std::list<IndexBuffer> mIbos;
};
