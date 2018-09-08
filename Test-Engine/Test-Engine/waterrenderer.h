#pragma once

#include "scenemanager.h"

class WaterRenderer {
public:
	WaterRenderer();
	WaterRenderer(glm::mat4 pProjection);
	void draw(std::vector<Water*> * pWaters, const glm::mat4 &pViewMatrix, Shader * pShader);
private:
	glm::mat4 mProjection;
	void drawArrays(unsigned int pVertexCount);
	void enableVertexAttribArray(unsigned int pSize);
};

