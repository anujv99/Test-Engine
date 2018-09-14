#include "skyboxrenderer.h"

SkyboxRenderer::SkyboxRenderer() {}

SkyboxRenderer::SkyboxRenderer(glm::mat4 pProjection) {
	mProjection = pProjection;
}

void SkyboxRenderer::draw(SkyBox * pSkybox, const glm::mat4 & pViewMatrix, Shader * pShader) {
	if (pSkybox == nullptr)
		return;

	glDepthFunc(GL_LEQUAL);
	pShader->bind();

	pShader->loadStoredUniform(mProjection, UNIFORM_MATRIX_PROJECTION);
	pShader->loadStoredUniform(pViewMatrix, UNIFORM_MATRIX_VIEW);

	pSkybox->mVAO->bind();
	pSkybox->mTextureID->bind(0);
	enableVertexAttribArray(0);
	drawArrays(pSkybox->mVertexCount);
	glDepthFunc(GL_LESS);
}

void SkyboxRenderer::drawArrays(unsigned int pVertexCount) {
	glDrawArrays(GL_TRIANGLES, 0, pVertexCount);
}

void SkyboxRenderer::enableVertexAttribArray(unsigned int pSize) {
	for (unsigned int i = 0; i <= pSize; i++) {
		glEnableVertexAttribArray(i);
	}
}
