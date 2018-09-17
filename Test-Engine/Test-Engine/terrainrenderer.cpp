#include "terrainrenderer.h"

TerrainRenderer::TerrainRenderer() {}

TerrainRenderer::TerrainRenderer(glm::mat4 pProjection) {
	mProjection = pProjection;
}

void TerrainRenderer::draw(std::vector<Terrain*>* pTerrains, const glm::mat4 & pViewMatrix, Shader * pShader) {
	pShader->bind();
	pShader->loadStoredUniform(pViewMatrix, UNIFORM_MATRIX_VIEW);
	pShader->loadStoredUniform(mProjection, UNIFORM_MATRIX_PROJECTION);
	pShader->loadStoredUniform(glm::mat4(1.0f), UNIFORM_MATRIX_MODEL);

	for (auto const &pTerrain : *pTerrains) {
		pTerrain->mVAO->bind();
		if (pTerrain->mTexture != nullptr) {
			enableVertexAttribArray(2);
			pTerrain->mTexture->bind(0);
		} else {
			enableVertexAttribArray(3);
		}
		drawElements(pTerrain->mVertexCount);
	}
}

void TerrainRenderer::drawElements(unsigned int pVertexCount) {
	glDrawElements(GL_TRIANGLES, pVertexCount, GL_UNSIGNED_INT, (void*)0);
}

void TerrainRenderer::enableVertexAttribArray(unsigned int pSize) {
	for (unsigned int i = 0; i <= pSize; i++) {
		glEnableVertexAttribArray(i);
	}
}
