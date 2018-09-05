#pragma once

#include "basicloader.h"
#include "terraingenerator.h"

class AssetManager {
public:
	AssetManager();
	Model * loadModel(std::string path);
	Terrain * generateTerrain(unsigned int pVertexCount, unsigned int pSize);
private:
	std::list<Model> mModels;
	std::list<Terrain> mTerrains;
};

