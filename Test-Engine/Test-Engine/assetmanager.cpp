#include "assetmanager.h"

AssetManager::AssetManager() {}

Model * AssetManager::loadModel(std::string path) {
	auto tModel = BasicLoader::loadModel(path);
	if (tModel.mVAO == nullptr) {
		printf("ASSET_MANAGER::Unable to load model\n");
		return nullptr;
	}
	mModels.push_back(tModel);
	return &mModels.back();
}

Terrain * AssetManager::generateTerrain(unsigned int pVertexCount, unsigned int pSize, std::string pHmName) {
	auto tTerrain = TerrainGenerator::createTerrain(pVertexCount, pSize, pHmName);
	mTerrains.push_back(tTerrain);
	return &mTerrains.back();
}

DirectionalLight * AssetManager::createDirectionalLight(glm::vec3 pDirection, glm::vec3 pColor) {
	auto tDirectionalLight = DirectionalLightGenerator::createDirectionalLight(pDirection, pColor);
	mDirectionalLights.push_back(tDirectionalLight);
	return &mDirectionalLights.back();
}

Water * AssetManager::addWater(unsigned int pVertexCount, unsigned int pSize) {
	auto tWater = WaterGenerator::addWater(pVertexCount, pSize);
	mWaters.push_back(tWater);
	return &mWaters.back();
}

SkyBox * AssetManager::addSkybox(std::string pFileName, std::string pFileExtension) {
	auto tSkybox = SkyboxLoader::loadSkybox(pFileName, pFileExtension);
	mSkyboxes.push_back(tSkybox);
	return &mSkyboxes.back();
}

Grass * AssetManager::generateGrass() {
	auto tGrass = GrassGenerator::generateGrass();
	mGrasses.push_back(tGrass);
	return &mGrasses.back();
}
