#include "basicloader.h"

bool BasicLoader::loadModel(std::string pFilePath) {
	std::ifstream tInFile("res/models/" + pFilePath + ".toxic", std::ios::in | std::ios::binary);
	if (!tInFile) {
		printf("LOADER::Unable to load model : %s\n", pFilePath.c_str());
		return false;
	}

}
