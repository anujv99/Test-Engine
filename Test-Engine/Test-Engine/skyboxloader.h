#pragma once

#include "openglresources.h"
#include <string>

struct SkyBox {
	VertexArray * mVAO;
	unsigned int mVertexCount;
	Texture * mTextureID;
	SkyBox() :
		mVAO(nullptr), mVertexCount(0), mTextureID(nullptr) {}

	SkyBox(VertexArray * pVAO, unsigned int pVertexCount, Texture * pTextureID) :
		mVAO(pVAO), mVertexCount(pVertexCount), mTextureID(pTextureID) {}
};

class SkyboxLoader {
public:
	static SkyBox loadSkybox(const std::string &pFileName, const std::string &pFileExtension);
};
