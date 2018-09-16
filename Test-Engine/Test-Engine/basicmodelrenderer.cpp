#include "basicmodelrenderer.h"

BasicModelRenderer::BasicModelRenderer(glm::mat4 pProjection) {
	mProjection = pProjection;
}

void BasicModelRenderer::draw(std::vector<Model*> * pModels, const glm::mat4 &pViewMatrix, Shader * pShader) {
	pShader->bind();
	pShader->loadStoredUniform(pViewMatrix, UNIFORM_MATRIX_VIEW);
	pShader->loadStoredUniform(mProjection, UNIFORM_MATRIX_PROJECTION);

	for (auto const &pModel : *pModels) {
		auto tModelMat = createModelMatrix(pModel->mPosition, pModel->mRotation, pModel->mScale);
		pShader->loadStoredUniform(tModelMat, UNIFORM_MATRIX_MODEL);

		if (pModel->mDiffuseTex != nullptr) {
			pModel->mDiffuseTex->bind(0);
		}

		pModel->mVAO->bind();
		enableVertexAttribArray(3);
		drawElements(pModel->mVertexCount);
	}
}

glm::mat4 BasicModelRenderer::createModelMatrix(const glm::vec3 &pPos, const glm::vec3 &pRot, const float &pScale) {
	glm::mat4 tModel = glm::mat4(1.0f);
	tModel = glm::scale(tModel, glm::vec3(pScale));
	tModel = glm::rotate(tModel, glm::radians(pRot.x), glm::vec3(1, 0, 0));
	tModel = glm::rotate(tModel, glm::radians(pRot.y), glm::vec3(0, 1, 0));
	tModel = glm::rotate(tModel, glm::radians(pRot.z), glm::vec3(0, 0, 1));
	tModel = glm::translate(tModel, pPos);
	return tModel;
}

void BasicModelRenderer::drawElements(unsigned int pVertexCount) {
	glDrawElements(GL_TRIANGLES, pVertexCount, GL_UNSIGNED_INT, (void*)0);
}

void BasicModelRenderer::enableVertexAttribArray(unsigned int pSize) {
	for (unsigned int i = 0; i < pSize; i++) {
		glEnableVertexAttribArray(i);
	}
}
