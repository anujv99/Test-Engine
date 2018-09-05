#pragma once

#include "basicloader.h"

class AssetManager {
public:
	AssetManager();
	Model * loadModel(std::string path);
private:
	std::vector<Model> mModels;
};

