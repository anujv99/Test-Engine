#include "grassloader.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>

#include "basicloader.h"

bool GrassLoader::isModelGenerated = false;
VertexArray * GrassLoader::mVAO = nullptr;
unsigned int GrassLoader::mVertexCount = 0;

Grass GrassLoader::generateGrass() {
	auto tModel = BasicLoader::loadModel("grass/grass");

	return Grass(tModel.mVAO, tModel.mVertexCount, tModel.mDiffuseTex);
}
