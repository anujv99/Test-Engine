#pragma once

#include "scene.h"
#include "assetmanager.h"
#include "shadermanager.h"
#include "lualoader.h"

class SceneManager : LuaLoader {
public:
	SceneManager();
	SceneManager(AssetManager * pAssetManager);
	inline Scene * getActiveScene() { return mActiveScene; }
public:
	static Shader * getBasicModelShader() { return mBasicModelShader; }
	static Shader * getTerrainShaer() { return mTerrainShader; }
	static Shader * getWaterShader() { return mWaterShader; }
private:
	static AssetManager * mAssetManager;
	static std::vector<Scene> mScenes;
	static Scene * mActiveScene;
private:
	static Shader * mBasicModelShader;
	static Shader * mTerrainShader;
	static Shader * mWaterShader;
private:
	static int loadTerrain(lua_State * L);
	static int setSun(lua_State * L);
private:
	void commitFunctions() override;
};
