#pragma once

#include "shadermanager.h"

class AntiAliasing {
public:
	static bool start(unsigned int pWindowWidth, unsigned int pWindowHeight);
	static void bind();
	static void renderQuad();
	static void cleanUP();
	static void setWireframeBool(bool * pWireframe) { mIsWireframe = pWireframe; }
	static unsigned int getMiltisampledFBO() { return mMultisampledFBO; }
private:
	static unsigned int mMultisampledFBO, mIntermediateFBO;
	static unsigned int mTextureMultisampled, mTextureIntermediate;
	static unsigned int mRenderbufferMultisampled;
	static unsigned int mWidth, mHeight;
	static void render();
	static void createQuad();
	static unsigned int mVAO, mVBO1, mVBO2;
	static unsigned int mVertexCount;
	static Shader * mFboShader;
private:
	static bool * mIsWireframe;
};
