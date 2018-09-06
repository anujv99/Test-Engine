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

Terrain * AssetManager::generateTerrain(unsigned int pVertexCount, unsigned int pSize) {
	auto tTerrain = TerrainGenerator::createTerrain(pVertexCount, pSize);
	mTerrains.push_back(tTerrain);
	return &mTerrains.back();
}

DirectionalLight * AssetManager::createDirectionalLight(glm::vec3 pDirection, glm::vec3 pColor) {
	auto tDirectionalLight = DirectionalLightGenerator::createDirectionalLight(pDirection, pColor);
	mDirectionalLights.push_back(tDirectionalLight);
	return &mDirectionalLights.back();
}
