#pragma once

#include "scenemanager.h"
#include "shadermanager.h"

class BasicModelRenderer {
public:
	BasicModelRenderer(){}
	BasicModelRenderer(glm::mat4 pProjection);
	void draw(std::vector<Model*> * pModels, const glm::mat4 &pViewMatrix, Shader * pShader);
private:
	glm::mat4 mProjection;
	glm::mat4 createModelMatrix(const glm::vec3 &pPos, const glm::vec3 &pRot, const float &pScale);
	void drawElements(unsigned int pVertexCount);
	void enableVertexAttribArray(unsigned int pSize);
};
