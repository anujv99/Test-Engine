#include "scenemanager.h"

#include "collisioninterface.h"

Shader * SceneManager::mBasicModelShader;
Shader * SceneManager::mTerrainShader;
Shader * SceneManager::mWaterShader;
Shader * SceneManager::mSkyboxShader;
Shader * SceneManager::mGrassShader;
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
	mGrassShader = ShaderManager::addShader(SHADER_GRASS, "grass");

	mBasicModelShader->bind();
	mBasicModelShader->setInt(0, "tDiffuseTexture");
	mBasicModelShader->unBind();

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

	auto tModel = mAssetManager->loadModel("tree/tree1");
	mActiveScene->addModel(tModel);
	Player::setPlayer(tModel, mActiveScene->getTerrains()->at(0));
	//mActiveScene->addWater(mAssetManager->addWater(100, 512));
	mActiveScene->addSkybox(mAssetManager->addSkybox("cloudy", ".png"));

	CollisionInterface::addTerrainCollidor(mActiveScene->getTerrains()->at(0));

}

void SceneManager::commitFunctions() {
	lua_register(L, "createTerrain", loadTerrain);
	lua_register(L, "setSun", setSun);
}

int SceneManager::loadTerrain(lua_State * L) {
	int argc = lua_gettop(L);
	unsigned int tVCount, tSize;
	float tAmplitude;
	std::string tHmName, tTexName;
	if (argc != 5) {
		std::cout << "LUA::Invalid arguments passed!" << std::endl;
		return -1;
	}
	tVCount = (int)lua_tointeger(L, 1);
	tSize = (int)lua_tointeger(L, 2);
	tAmplitude = (float)lua_tonumber(L, 3);
	tHmName = lua_tostring(L, 4);
	tTexName = lua_tostring(L, 5);
	mActiveScene->addTerrain(mAssetManager->generateTerrain(tVCount, tSize, tAmplitude, tHmName, tTexName));
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
		tData[i - 1] = (float)lua_tonumber(L, i);
	}
	glm::vec3 tDir(tData[0], tData[1], tData[2]);
	glm::vec3 tColor(tData[3], tData[4], tData[5]);
	tColor /= 255;

	mActiveScene->addSun(mAssetManager->createDirectionalLight(tDir, tColor));
	return 0;
}
