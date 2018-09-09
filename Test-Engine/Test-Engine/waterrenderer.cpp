#include "waterrenderer.h"

WaterRenderer::WaterRenderer() {
}

WaterRenderer::WaterRenderer(glm::mat4 pProjection) {
	mProjection = pProjection;
}

WaterRenderer::~WaterRenderer() {
}

void WaterRenderer::draw(Water * pWater, const glm::mat4 &pViewMatrix, glm::vec3 pCameraPos, Shader * pShader, unsigned int pReflectionTexture, unsigned int pRefractionTexture, unsigned int pRefractionDepthTexture) {
	pShader->bind();

	connectTexture(0, pReflectionTexture);
	connectTexture(1, pRefractionTexture);
	connectTexture(2, pRefractionDepthTexture);

	pShader->loadStoredUniform(pViewMatrix, UNIFORM_MATRIX_VIEW);
	pShader->loadStoredUniform(mProjection, UNIFORM_MATRIX_PROJECTION);
	pShader->loadStoredUniform(glm::mat4(1.0f), UNIFORM_MATRIX_MODEL);
	pShader->loadStoredUniform(pCameraPos, UNIFORM_CAMERA_POSITION);

	time += WAVE_SPEED;
	pShader->setFloat(time, "waveTime");

	pWater->mVAO->bind();
	enableVertexAttribArray(2);
	drawArrays(pWater->mVertexCount);
	resetTexture();
}

void WaterRenderer::drawArrays(unsigned int pVertexCount) {
	glDrawArrays(GL_TRIANGLES, 0, pVertexCount);
}

void WaterRenderer::enableVertexAttribArray(unsigned int pSize) {
	for (unsigned int i = 0; i <= pSize; i++) {
		glEnableVertexAttribArray(i);
	}
}

void WaterRenderer::connectTexture(unsigned int pIndex, unsigned int pTexID) {
	glActiveTexture(GL_TEXTURE0 + pIndex);
	glBindTexture(GL_TEXTURE_2D, pTexID);
}

void WaterRenderer::resetTexture() {
	glActiveTexture(GL_TEXTURE0);
}
