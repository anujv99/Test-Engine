#include "masterrenderer.h"

#define __MSAA__

MasterRenderer::MasterRenderer(const unsigned int pWindowWidth, const unsigned int pWindowHeight, CameraMaster * pCamera) {
	glEnable(GL_DEBUG_OUTPUT);
	mCamera = pCamera;
	mProjection = glm::perspective(glm::radians(45.0f), (float)pWindowWidth / (float)pWindowHeight, 0.1f, 1000.0f);
	mBasicRenderer = BasicModelRenderer(mProjection);
	mTerrainRenderer = TerrainRenderer(mProjection);
	mWaterFbos = WaterFBOs(pWindowWidth, pWindowHeight);
	mWaterRenderer = WaterRenderer(mProjection);
	mSkyboxRenderer = SkyboxRenderer(mProjection);
	mGrassRenderer = GrassRenderer(mProjection);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_CLIP_DISTANCE0);

#ifdef __MSAA__
	AntiAliasing::start(pWindowWidth, pWindowHeight);
#endif // __MSAA__
}

void MasterRenderer::draw(Scene * pScene) {
	clear();
#ifdef __MSAA__
	AntiAliasing::bind();
#endif // __MSAA__
	
	drawAssets(pScene, mCamera->getViewMatrix());

#ifdef __MSAA__
	AntiAliasing::renderQuad();
#endif // !__MSAA__
}

void MasterRenderer::cleanUP() {
	AntiAliasing::cleanUP();
	mWaterFbos.cleanUP();
}

void MasterRenderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::drawAssets(Scene * pScene, const glm::mat4 & pViewMat) {
	mGrassRenderer.draw(pScene->getGrass(), pViewMat, SceneManager::getGrassShader());
	mBasicRenderer.draw(pScene->getBasicModels(), pViewMat, SceneManager::getBasicModelShader());
	mTerrainRenderer.draw(pScene->getTerrains(), pViewMat, SceneManager::getTerrainShaer());
	setSun(pScene->getSun(), SceneManager::getTerrainShaer());
	setSun(pScene->getSun(), SceneManager::getWaterShader());
	processAndRenderWater(pScene, pViewMat);
	mSkyboxRenderer.draw(pScene->getSkyBox(), pViewMat, SceneManager::getSkyboxShader());
}

void MasterRenderer::setSun(DirectionalLight * pSun, Shader * pShader) {
	pShader->bind();
	pShader->loadStoredUniform(pSun->mDirection, UNIFORM_SUN_DIRECTION);
	pShader->loadStoredUniform(pSun->mColor, UNIFORM_SUN_COLOR);
}

void MasterRenderer::processAndRenderWater(Scene * pScene, const glm::mat4 & pViewMat) {

	if (pScene->getWaters()->size() == 0) {
		return;
	}

	auto tWater = pScene->getWaters()->at(0);

	mWaterFbos.bindRefractionFrameBuffer();
	setClipPlane(SceneManager::getTerrainShaer(), glm::vec4(0, -1, 0, tWater->mHeight + 0.5f));
	mTerrainRenderer.draw(pScene->getTerrains(), pViewMat, SceneManager::getTerrainShaer());

	mWaterFbos.bindReflectionFrameBuffer();
	setClipPlane(SceneManager::getTerrainShaer(), glm::vec4(0, 1, 0, tWater->mHeight));
	mTerrainRenderer.draw(pScene->getTerrains(), mCamera->getInvertedViewMatrix(tWater->mHeight), SceneManager::getTerrainShaer());

#ifdef __MSAA__
	mWaterFbos.unbindCurrentFrameBuffer(AntiAliasing::getMiltisampledFBO());
#else
	mWaterFbos.unbindCurrentFrameBuffer(0);
#endif
	setClipPlane(SceneManager::getTerrainShaer(), glm::vec4(0));

	mWaterRenderer.draw(tWater, pViewMat, mCamera->getCameraPos(), SceneManager::getWaterShader(), mWaterFbos.getReflectionTexture(), 
		mWaterFbos.getRefractionTexture(), mWaterFbos.getRefractionDepthTexture());
}

void MasterRenderer::setClipPlane(Shader * pShader, glm::vec4 pValue) {
	pShader->bind();
	pShader->loadStoredUniform(pValue, UNIFORM_CLIP_PLANE);
}
