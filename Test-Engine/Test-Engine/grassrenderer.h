#pragma once

#include "scenemanager.h"
#include "rendereressentials.h"

class GrassRenderer : public RendererEssentials {
public:
	GrassRenderer();
	GrassRenderer(glm::mat4 pProjection);
	void draw(Grass * pGrass, const glm::mat4 &pViewMatrix, Shader * pShader);
private:
	glm::mat4 mProjection;
};

