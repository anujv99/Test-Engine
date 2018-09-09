#pragma once

#include "scenemanager.h"

class WaterFBOs {
public:
	WaterFBOs();
	WaterFBOs(unsigned int pWidth, unsigned int pHeight);
	void cleanUP();
	void bindReflectionFrameBuffer();
	void bindRefractionFrameBuffer();
	void unbindCurrentFrameBuffer(unsigned int pFboID);
public:
	inline unsigned int getReflectionTexture() { return mReflectionTexture; }
	inline unsigned int getRefractionTexture() { return mRefractionTexture; }
	inline unsigned int getRefractionDepthTexture() { return mRefractionDepthTexture; }
private:
	void createReflectionFBO(unsigned int pWidth, unsigned int pHeight);
	void createRefractionFBO(unsigned int pWidth, unsigned int pHeight);
	unsigned int createFrameBuffer();
	int createTextureAttachment(unsigned int pWidth, unsigned int pHeight);
	int createDepthTextureAttachment(unsigned int pWidth, unsigned int pHeight);
	int createDepthBufferAttachment(unsigned int pWidth, unsigned int pHeight);
	void checkForErrors();

	void bindFrameBuffer(unsigned int pFboID, unsigned int pWidth, unsigned int pHeight);

private:
	unsigned int mReflectionFBO, mRefractionFBO;
	unsigned int mReflectionTexture, mRefractionTexture;
	unsigned int mReflectionDepthRBO, mRefractionDepthTexture;

	int REFLECTION_WIDTH = 1280/2;
	int REFLECTION_HEIGHT = 720/2;

	int REFRACTION_WIDTH = 1280;
	int REFRACTION_HEIGHT = 720;
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
};

