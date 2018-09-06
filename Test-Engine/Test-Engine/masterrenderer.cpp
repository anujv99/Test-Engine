#include "masterrenderer.h"

#define __MSAA__

MasterRenderer::MasterRenderer(const unsigned int pWindowWidth, const unsigned int pWindowHeight) {
	mProjection = glm::perspective(glm::radians(45.0f), (float)pWindowWidth / (float)pWindowHeight, 0.1f, 100.0f);
	mBasicRenderer = BasicModelRenderer(mProjection);
	mTerrainRenderer = TerrainRenderer(mProjection);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);

#ifdef __MSAA__
	AntiAliasing::start(pWindowWidth, pWindowHeight);
#endif // __MSAA__

}

void MasterRenderer::draw(Scene * pScene, const glm::mat4 &pViewMat) {
	clear();
#ifdef __MSAA__
	AntiAliasing::bind();
	drawAssets(pScene, pViewMat);
	AntiAliasing::renderQuad();
#endif // __MSAA__

#ifndef __MSAA__
	drawAssets(pScene, pViewMat);
#endif // !__MSAA__
}

void MasterRenderer::cleanUP() {
	AntiAliasing::cleanUP();
}

void MasterRenderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::drawAssets(Scene * pScene, const glm::mat4 & pViewMat) {
	mBasicRenderer.draw(pScene->getBasicModels(), pViewMat, SceneManager::getBasicModelShader());
	mTerrainRenderer.draw(pScene->getTerrains(), pViewMat, SceneManager::getTerrainShaer());
	mTerrainRenderer.setSun(pScene->getSun(), SceneManager::getTerrainShaer());
}
