#pragma once

#include "assetmanager.h"

class Scene {
public:
	Scene();
	~Scene();
public:
	void addModel(Model * pModel);
	inline std::vector<Model*> * getBasicModels() { return &mModels; }
private:
	std::vector<Model*> mModels;
};
