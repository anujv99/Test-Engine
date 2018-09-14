#pragma once

#include "scenemanager.h"

class SkyboxRenderer {
public:
	SkyboxRenderer();
	SkyboxRenderer(glm::mat4 pProjection);
	void draw(SkyBox * pSkybox, const glm::mat4 &pViewMatrix, Shader * pShader);
private:
	glm::mat4 mProjection;
	void drawArrays(unsigned int pVertexCount);
	void enableVertexAttribArray(unsigned int pSize);
};

