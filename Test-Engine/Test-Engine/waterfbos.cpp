#include "waterfbos.h"

WaterFBOs::WaterFBOs() {
}

WaterFBOs::WaterFBOs(unsigned int pWidth, unsigned int pHeight) {
	WINDOW_WIDTH = pWidth;
	WINDOW_HEIGHT = pHeight;
	createReflectionFBO(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	createRefractionFBO(REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void WaterFBOs::cleanUP() {
	glDeleteRenderbuffers(1, &mReflectionDepthRBO);
	glDeleteTextures(1, &mReflectionTexture);
	glDeleteTextures(1, &mRefractionTexture);
	glDeleteTextures(1, &mRefractionDepthTexture);
	glDeleteFramebuffers(1, &mReflectionFBO);
	glDeleteFramebuffers(1, &mRefractionFBO);
}

void WaterFBOs::createReflectionFBO(unsigned int pWidth, unsigned int pHeight) {
	mReflectionFBO = createFrameBuffer();
	mReflectionTexture = createTextureAttachment(pWidth, pHeight);
	mReflectionDepthRBO = createDepthBufferAttachment(pWidth, pHeight);
	checkForErrors();
}

void WaterFBOs::createRefractionFBO(unsigned int pWidth, unsigned int pHeight) {
	mRefractionFBO = createFrameBuffer();
	mRefractionTexture = createTextureAttachment(pWidth, pHeight);
	mRefractionDepthTexture = createDepthTextureAttachment(pWidth, pHeight);
	checkForErrors();
}

unsigned int WaterFBOs::createFrameBuffer() {
	unsigned int frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return frameBuffer;
}

int WaterFBOs::createTextureAttachment(unsigned int pWidth, unsigned int pHeight) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pWidth, pHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	return texture;
}

int WaterFBOs::createDepthTextureAttachment(unsigned int pWidth, unsigned int pHeight) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, pWidth, pHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
	return texture;
}

int WaterFBOs::createDepthBufferAttachment(unsigned int pWidth, unsigned int pHeight) {
	unsigned int depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pWidth, pHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	return depthBuffer;
}

void WaterFBOs::checkForErrors() {
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("MSAA::ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void WaterFBOs::bindFrameBuffer(unsigned int pFboID, unsigned int pWidth, unsigned int pHeight) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, pFboID);
	glViewport(0, 0, pWidth, pHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WaterFBOs::bindReflectionFrameBuffer() {
	bindFrameBuffer(mReflectionFBO, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void WaterFBOs::bindRefractionFrameBuffer() {
	bindFrameBuffer(mRefractionFBO, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void WaterFBOs::unbindCurrentFrameBuffer(unsigned int pFboID) {
	glBindFramebuffer(GL_FRAMEBUFFER, pFboID);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
