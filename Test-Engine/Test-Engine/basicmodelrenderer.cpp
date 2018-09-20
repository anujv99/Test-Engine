#include "basicmodelrenderer.h"

BasicModelRenderer::BasicModelRenderer(glm::mat4 pProjection) {
	mProjection = pProjection;
}

void BasicModelRenderer::draw(std::vector<Model*> * pModels, const glm::mat4 &pViewMatrix, Shader * pShader) {
	pShader->bind();
	pShader->loadStoredUniform(pViewMatrix, UNIFORM_MATRIX_VIEW);
	pShader->loadStoredUniform(mProjection, UNIFORM_MATRIX_PROJECTION);

	for (auto const &pModel : *pModels) {
		pShader->loadStoredUniform(pModel->mRigidBody->getModelMatrix(), UNIFORM_MATRIX_MODEL);

		if (pModel->mDiffuseTex != nullptr) {
			pModel->mDiffuseTex->bind(0);
		}

		pModel->mVAO->bind();
		enableVertexAttribArray(3);
		drawElements(pModel->mVertexCount);
	}
}

void BasicModelRenderer::drawElements(unsigned int pVertexCount) {
	glDrawElements(GL_TRIANGLES, pVertexCount, GL_UNSIGNED_INT, (void*)0);
}

void BasicModelRenderer::enableVertexAttribArray(unsigned int pSize) {
	for (unsigned int i = 0; i < pSize; i++) {
		glEnableVertexAttribArray(i);
	}
}
