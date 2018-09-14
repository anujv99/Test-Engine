#include "scenemanager.h"

Shader * SceneManager::mBasicModelShader;
Shader * SceneManager::mTerrainShader;
Shader * SceneManager::mWaterShader;
Shader * SceneManager::mSkyboxShader;
AssetManager * SceneManager::mAssetManager;
std::vector<Scene> SceneManager::mScenes;
Scene * SceneManager::mActiveScene;

SceneManager::SceneManager() {
}

SceneManager::SceneManager(AssetManager * pAssetManager) {
	mAssetManager = pAssetManager;
	mBasicModelShader = ShaderManager::addShader(SHADER_BASIC, "basic");
	mTerrainShader = ShaderManager::addShader(SHADER_TERRAIN, "terrain");
	mWaterShader = ShaderManager::addShader(SHADER_WATER, "water");
	mSkyboxShader = ShaderManager::addShader(SHADER_SKYBOX, "skybox");

	mWaterShader->bind();
	mWaterShader->setInt(0, "waterReflection");
	mWaterShader->setInt(1, "waterRefraction");
	mWaterShader->setInt(2, "waterRefractionDepth");
	mWaterShader->unBind();
	mActiveScene = nullptr;
	mScenes.push_back(Scene());
	mActiveScene = &mScenes[mScenes.size() - 1];

	load("sceneScript.lua");
	run();
	stop();

	//mActiveScene->addModel(mAssetManager->loadModel("chair1"));
	mActiveScene->addWater(mAssetManager->addWater(80, 200));
	mActiveScene->addSkybox(mAssetManager->addSkybox("cloudy", ".png"));
}

void SceneManager::commitFunctions() {
	lua_register(L, "createTerrain", loadTerrain);
	lua_register(L, "setSun", setSun);
}

int SceneManager::loadTerrain(lua_State * L) {
	int argc = lua_gettop(L);
	unsigned int tVCount, tSize;
	std::string tHmName;
	if (argc != 3) {
		std::cout << "LUA::Invalid arguments passed!" << std::endl;
		return -1;
	}
	tVCount = lua_tointeger(L, 1);
	tSize = lua_tointeger(L, 2);
	tHmName = lua_tostring(L, 3);
	mActiveScene->addTerrain(mAssetManager->generateTerrain(tVCount, tSize, tHmName));
	return 0;
}

int SceneManager::setSun(lua_State * L) {
	int argc = lua_gettop(L);
	if (argc != 6) {
		std::cout << "LUA::Invalid arguments passed!" << std::endl;
		return -1;
	}
	float tData[6];
	for (unsigned int i = 1; i <= 6; i++) {
		tData[i - 1] = lua_tointeger(L, i);
	}
	glm::vec3 tDir(tData[0], tData[1], tData[2]);
	glm::vec3 tColor(tData[3], tData[4], tData[5]);
	tColor /= 255;

	mActiveScene->addSun(mAssetManager->createDirectionalLight(tDir, tColor));
	return 0;
}
