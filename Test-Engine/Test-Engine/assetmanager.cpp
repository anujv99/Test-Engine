#include "assetmanager.h"

AssetManager::AssetManager() {}

Model * AssetManager::loadModel(std::string path) {
	auto tModel = BasicLoader::loadModel(path);
	if (tModel.mVAO == nullptr) {
		printf("ASSET_MANAGER::Unable to load model\n");
		return nullptr;
	}
	mModels.push_back(tModel);
	return &mModels[mModels.size() - 1];
}
