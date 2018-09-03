#pragma once

#include <string>
#include <fstream>
#include <ios>
#include <vector>

#include "vertexarray.h"

struct Model {
	VertexArray * mVAO;
	unsigned int mVertexCount;
	Model() :
		mVAO(nullptr), mVertexCount(-1) {
	}
	Model(VertexArray * pVAO, unsigned int pVertexCount) :
		mVAO(pVAO), mVertexCount(pVertexCount) {
	}
};

class BasicLoader {
public:
	static Model loadModel(std::string pFilePath);
private:
	static int readINT(std::ifstream * pInFile);
	static void readBuffer(std::ifstream * pInFile, void * pStream, unsigned int pBufferSize);
	static VertexArray * createVAO();
	static VertexBuffer * createVBO(const float * pData, unsigned int pSize);
	static IndexBuffer * createIBO(const int * pData, unsigned int pSize);
private:
	static std::vector<VertexArray> mVaos;
	static std::vector<VertexBuffer> mVbos;
	static std::vector<IndexBuffer> mIbos;
};
