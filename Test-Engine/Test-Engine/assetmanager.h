#pragma once

#include "basicloader.h"
#include "terraingenerator.h"
#include "directionallightgenerator.h"
#include "watergenerator.h"
#include "skyboxloader.h"

class AssetManager {
public:
	AssetManager();
	Model * loadModel(std::string path);
	Terrain * generateTerrain(unsigned int pVertexCount, unsigned int pSize, std::string pHmName);
	DirectionalLight * createDirectionalLight(glm::vec3 pDirection, glm::vec3 pColor);
	Water * addWater(unsigned int pVertexCount, unsigned int pSize);
	SkyBox * addSkybox(std::string pFileName, std::string pFileExtension);
private:
	std::list<Model> mModels;
	std::list<Terrain> mTerrains;
	std::list<DirectionalLight> mDirectionalLights;
	std::list<Water> mWaters;
	std::list<SkyBox> mSkyboxes;
};

