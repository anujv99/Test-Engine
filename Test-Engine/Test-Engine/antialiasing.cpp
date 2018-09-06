#include "antialiasing.h"

#include <glad/glad.h>
#include <iostream>

#define SAMPLES 4

unsigned int AntiAliasing::mMultisampledFBO;
unsigned int AntiAliasing::mIntermediateFBO;
unsigned int AntiAliasing::mTextureMultisampled;
unsigned int AntiAliasing::mTextureIntermediate;
unsigned int AntiAliasing::mRenderbufferMultisampled;
unsigned int AntiAliasing::mWidth;
unsigned int AntiAliasing::mHeight;
unsigned int AntiAliasing::mVAO;
unsigned int AntiAliasing::mVBO1;
unsigned int AntiAliasing::mVBO2;
unsigned int AntiAliasing::mVertexCount;
Shader * AntiAliasing::mFboShader;
bool * AntiAliasing::mIsWireframe;

bool AntiAliasing::start(unsigned int pWindowWidth, unsigned int pWindowHeight) {
	mWidth = pWindowWidth;
	mHeight = pWindowHeight;
	glGenFramebuffers(1, &mMultisampledFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, mMultisampledFBO);

	glGenTextures(1, &mTextureMultisampled);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, mTextureMultisampled);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, SAMPLES, GL_RGB, pWindowWidth, pWindowHeight, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, mTextureMultisampled, 0);

	glGenRenderbuffers(1, &mRenderbufferMultisampled);
	glBindRenderbuffer(GL_RENDERBUFFER, mRenderbufferMultisampled);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, SAMPLES, GL_DEPTH24_STENCIL8, pWindowWidth, pWindowHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderbufferMultisampled);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("MSAA::ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenFramebuffers(1, &mIntermediateFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, mIntermediateFBO);
	
	glGenTextures(1, &mTextureIntermediate);
	glBindTexture(GL_TEXTURE_2D, mTextureIntermediate);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pWindowWidth, pWindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureIntermediate, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("MSAA::ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	mFboShader = ShaderManager::addShader(SHADER_FBO_QUAD, "fboQuad");

	createQuad();

	return true;
}

void AntiAliasing::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, mMultisampledFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void AntiAliasing::renderQuad() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mMultisampledFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mIntermediateFBO);
	glBlitFramebuffer(0, 0, mWidth, mHeight, 0, 0, mWidth, mHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (*mIsWireframe == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		render();
	}
}

void AntiAliasing::cleanUP() {
	glDeleteBuffers(1, &mVBO1);
	glDeleteBuffers(1, &mVBO2);
	glDeleteVertexArrays(1, &mVAO);
	glDeleteRenderbuffers(1, &mRenderbufferMultisampled);
	glDeleteTextures(1, &mTextureMultisampled);
	glDeleteTextures(1, &mTextureIntermediate);
	glDeleteFramebuffers(1, &mMultisampledFBO);
	glDeleteFramebuffers(1, &mIntermediateFBO);
}

void AntiAliasing::render() {
	glDisable(GL_DEPTH_TEST);
	mFboShader->bind();
	glBindTexture(GL_TEXTURE_2D, mTextureIntermediate);
	glBindVertexArray(mVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
	glEnable(GL_DEPTH_TEST);
}

void AntiAliasing::createQuad() {
	float quadVertices[] = {
		-1.0f,  1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f,

		-1.0f,  1.0f,
		1.0f, -1.0f,
		1.0f,  1.0f
	};

	float quadTexCoords[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO1);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO1);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(1, &mVBO2);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO2);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), quadTexCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	mVertexCount = 6;
}
