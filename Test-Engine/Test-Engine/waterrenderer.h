#pragma once

#include "waterfbos.h"

class WaterRenderer {
public:
	WaterRenderer();
	WaterRenderer(glm::mat4 pProjection);
	~WaterRenderer();
	void draw(Water * pWater, const glm::mat4 &pViewMatrix, glm::vec3 pCameraPos, Shader * pShader, unsigned int pReflectionTexture, unsigned int pRefractionTexture, unsigned int pRefractionDepthTexture);
private:
	glm::mat4 mProjection;
	void drawArrays(unsigned int pVertexCount);
	void enableVertexAttribArray(unsigned int pSize);
	void connectTexture(unsigned int pIndex, unsigned int pTexID);
	void resetTexture();
private:
	float WAVE_SPEED = 0.004f;
	float time = 0.0f;
};

