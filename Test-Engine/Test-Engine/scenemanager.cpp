#include "scenemanager.h"

Shader * SceneManager::mBasicModelShader;

SceneManager::SceneManager() {}

SceneManager::SceneManager(AssetManager * pAssetManager) {
	mAssetManager = pAssetManager;
	mBasicModelShader = ShaderManager::addShader(SHADER_BASIC, "basic");

	mActiveScene = nullptr;
	mScenes.push_back(Scene());
	mActiveScene = &mScenes[mScenes.size() - 1];
	mActiveScene->addModel(mAssetManager->loadModel("chair1"));
}
