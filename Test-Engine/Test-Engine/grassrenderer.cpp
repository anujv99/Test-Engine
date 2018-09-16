#include "grassrenderer.h"

GrassRenderer::GrassRenderer() {}

GrassRenderer::GrassRenderer(glm::mat4 pProjection) {
	mProjection = pProjection;
}

void GrassRenderer::draw(Grass * pGrass, const glm::mat4 &pViewMatrix, Shader * pShader) {
	if (pGrass == nullptr) {
		return;
	}

	pShader->bind();
	pShader->loadStoredUniform(mProjection, UNIFORM_MATRIX_PROJECTION);
	pShader->loadStoredUniform(pViewMatrix, UNIFORM_MATRIX_VIEW);

	pGrass->mVAO->bind();
	enableVertexAttribArray(0);
	drawPoints(pGrass->mVertexCount);
}

