#pragma once

#include <list>

#include "vertexarray.h"
#include "Texture.h"
#include "indexbuffer.h"

class OpenGLResources {
public:
	static void cleanUP();
public:
	static VertexArray * createVAO();
	static VertexBuffer * createVBO(const float * pData, unsigned int pSize);
	static IndexBuffer * createIBO(const int * pData, unsigned int pSize);
	static Texture * createTexture();
	static Texture * createTexture(int ptexType);
private:
	static std::list<VertexArray> mVaos;
	static std::list<VertexBuffer> mVbos;
	static std::list<IndexBuffer> mIbos;
	static std::list<Texture> mTextures;
};

