#include "openglresources.h"

std::list<VertexArray> OpenGLResources::mVaos;
std::list<VertexBuffer> OpenGLResources::mVbos;
std::list<IndexBuffer> OpenGLResources::mIbos;
std::list<Texture> OpenGLResources::mTextures;

VertexArray * OpenGLResources::createVAO() {
	auto tVao = VertexArray();
	mVaos.push_back(tVao);
	return &mVaos.back();
}

VertexBuffer * OpenGLResources::createVBO(const float * pData, unsigned int pSize) {
	auto tVbo = VertexBuffer(pData, pSize);
	mVbos.push_back(tVbo);
	return &mVbos.back();
}

IndexBuffer * OpenGLResources::createIBO(const int * pData, unsigned int pSize) {
	auto tIbo = IndexBuffer(pData, pSize);
	mIbos.push_back(tIbo);
	return &mIbos.back();
}

Texture * OpenGLResources::createTexture() {
	auto tTexture = Texture();
	mTextures.push_back(tTexture);
	return &mTextures.back();
}

void OpenGLResources::cleanUP() {
	for (auto &sBuffer : mIbos) {
		sBuffer.cleanUP();
	}
	for (auto &sBuffer : mVbos) {
		sBuffer.cleanUP();
	}
	for (auto &sVAO : mVaos) {
		sVAO.cleanUP();
	}
	for (auto &sTex : mTextures) {
		sTex.cleanUP();
	}
}