#include "masterrenderer.h"

MasterRenderer::MasterRenderer(const unsigned int pWindowWidth, const unsigned int pWindowHeight) {
	mProjection = glm::perspective(glm::radians(45.0f), (float)pWindowWidth / (float)pWindowHeight, 0.1f, 100.0f);
	mBasicRenderer = BasicModelRenderer(mProjection);
	mTerrainRenderer = TerrainRenderer(mProjection);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
}

void MasterRenderer::draw(Scene * pScene, const glm::mat4 &mViewMat) {
	clear();
	mBasicRenderer.draw(pScene->getBasicModels(), mViewMat, SceneManager::getTerrainShaer());
	mTerrainRenderer.draw(pScene->getTerrains(), mViewMat, SceneManager::getTerrainShaer());
}

void MasterRenderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
