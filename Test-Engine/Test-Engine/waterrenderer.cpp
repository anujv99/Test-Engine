#include "waterrenderer.h"

WaterRenderer::WaterRenderer() {
}

WaterRenderer::WaterRenderer(glm::mat4 pProjection) {
	mProjection = pProjection;
}

void WaterRenderer::draw(std::vector<Water*>* pWaters, const glm::mat4 & pViewMatrix, Shader * pShader) {
	pShader->bind();
	pShader->loadStoredUniform(pViewMatrix, UNIFORM_MATRIX_VIEW);
	pShader->loadStoredUniform(mProjection, UNIFORM_MATRIX_PROJECTION);
	pShader->loadStoredUniform(glm::mat4(1.0f), UNIFORM_MATRIX_MODEL);

	for (auto const &pWater : *pWaters) {
		pWater->mVAO->bind();
		enableVertexAttribArray(1);
		drawArrays(pWater->mVertexCount);
	}

}

void WaterRenderer::drawArrays(unsigned int pVertexCount) {
	glDrawArrays(GL_TRIANGLES, 0, pVertexCount);
}

void WaterRenderer::enableVertexAttribArray(unsigned int pSize) {
	for (unsigned int i = 0; i <= pSize; i++) {
		glEnableVertexAttribArray(i);
	}
}
