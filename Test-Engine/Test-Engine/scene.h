#pragma once

#include "assetmanager.h"

class Scene {
public:
	Scene();
	~Scene();
public:
	void addModel(Model * pModel);
	void addTerrain(Terrain * pTerrain);
	void addSun(DirectionalLight * pSun);
	void addWater(Water * pWater);
	void addSkybox(SkyBox * pSkyBox);

	inline std::vector<Model*> * getBasicModels() { return &mModels; }
	inline std::vector<Terrain*> * getTerrains() { return &mTerrains; }
	inline DirectionalLight * getSun() { return mSun; }
	inline std::vector<Water*> * getWaters() { return &mWaters; }
	inline SkyBox * getSkyBox() { return mSkyBox; }
private:
	std::vector<Water*> mWaters;
	std::vector<Model*> mModels;
	std::vector<Terrain*> mTerrains;
	SkyBox * mSkyBox;
	DirectionalLight * mSun;
};
