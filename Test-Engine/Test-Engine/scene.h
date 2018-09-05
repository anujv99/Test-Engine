#pragma once

#include "assetmanager.h"

class Scene {
public:
	Scene();
	~Scene();
public:
	void addModel(Model * pModel);
	void addTerrain(Terrain * pTerrain);
	inline std::vector<Model*> * getBasicModels() { return &mModels; }
	inline std::vector<Terrain*> * getTerrains() { return &mTerrains; }
private:
	std::vector<Model*> mModels;
	std::vector<Terrain*> mTerrains;
};
