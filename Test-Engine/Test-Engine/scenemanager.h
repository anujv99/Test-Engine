#pragma once

#include "scene.h"
#include "assetmanager.h"
#include "shadermanager.h"

class SceneManager {
public:
	SceneManager();
	SceneManager(AssetManager * pAssetManager);
	inline Scene * getActiveScene() { return mActiveScene; }
public:
	static Shader * getBasicModelShader() { return mBasicModelShader; }
private:
	AssetManager * mAssetManager;
	std::vector<Scene> mScenes;
	Scene * mActiveScene;
private:
	static Shader * mBasicModelShader;
};
