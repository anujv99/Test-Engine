#pragma once

#include "basicloader.h"
#include "terraingenerator.h"
#include "directionallightgenerator.h"

class AssetManager {
public:
	AssetManager();
	Model * loadModel(std::string path);
	Terrain * generateTerrain(unsigned int pVertexCount, unsigned int pSize);
	DirectionalLight * createDirectionalLight(glm::vec3 pDirection, glm::vec3 pColor);
private:
	std::list<Model> mModels;
	std::list<Terrain> mTerrains;
	std::list<DirectionalLight> mDirectionalLights;
};

