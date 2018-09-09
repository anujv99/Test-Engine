#include "scenemanager.h"

Shader * SceneManager::mBasicModelShader;
Shader * SceneManager::mTerrainShader;
Shader * SceneManager::mWaterShader;

SceneManager::SceneManager() {}

SceneManager::SceneManager(AssetManager * pAssetManager) {
	mAssetManager = pAssetManager;
	mBasicModelShader = ShaderManager::addShader(SHADER_BASIC, "basic");
	mTerrainShader = ShaderManager::addShader(SHADER_TERRAIN, "terrain");
	mWaterShader = ShaderManager::addShader(SHADER_WATER, "water");

	mWaterShader->bind();
	mWaterShader->setInt(0, "waterReflection");
	mWaterShader->setInt(1, "waterRefraction");
	mWaterShader->setInt(2, "waterRefractionDepth");
	mWaterShader->unBind();

	mActiveScene = nullptr;
	mScenes.push_back(Scene());
	mActiveScene = &mScenes[mScenes.size() - 1];
	//mActiveScene->addModel(mAssetManager->loadModel("chair1"));
	mActiveScene->addTerrain(mAssetManager->generateTerrain(64, 50));
	mActiveScene->addSun(mAssetManager->createDirectionalLight(glm::vec3(-1), glm::vec3(1)));
	mActiveScene->addWater(mAssetManager->addWater(20, 50));
}
