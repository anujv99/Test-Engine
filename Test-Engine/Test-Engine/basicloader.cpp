#include "basicloader.h"

std::vector<VertexArray> BasicLoader::mVaos;
std::vector<VertexBuffer> BasicLoader::mVbos;
std::vector<IndexBuffer> BasicLoader::mIbos;

Model BasicLoader::loadModel(std::string pFilePath) {
	std::ifstream tInFile("res/models/" + pFilePath + ".toxic", std::ios::in | std::ios::binary);
	if (!tInFile) {
		printf("LOADER::Unable to open file : %s\n", pFilePath.c_str());
		tInFile.close();
		return Model();
	}

	int tVerticesSize = readINT(&tInFile);
	float * tVertices = new float[tVerticesSize / sizeof(float)];
	readBuffer(&tInFile, (void*)tVertices, tVerticesSize);

	int tNormalsSize = readINT(&tInFile);
	float * tNormals = new float[tNormalsSize / sizeof(float)];
	readBuffer(&tInFile, (void*)tNormals, tNormalsSize);

	int tTexCoordsSize = readINT(&tInFile);
	float * tTexCoords = new float[tTexCoordsSize / sizeof(float)];
	readBuffer(&tInFile, (void*)tTexCoords, tTexCoordsSize);

	int tIndicesSize = readINT(&tInFile);
	int * tIndices = new int[tIndicesSize / sizeof(int)];
	readBuffer(&tInFile, (void*)tIndices, tIndicesSize);

	tInFile.close();

	auto tVao = createVAO();
	tVao->bind();

	auto tVbo = createVBO(tVertices, tVerticesSize);
	tVbo->bind();
	tVao->addVertexBuffer(0, 3);
	tVbo->unBind();

	tVbo = createVBO(tNormals, tNormalsSize);
	tVbo->bind();
	tVao->addVertexBuffer(0, 3);
	tVbo->unBind();

	tVbo = createVBO(tTexCoords, tTexCoordsSize);
	tVbo->bind();
	tVao->addVertexBuffer(0, 2);
	tVbo->unBind();

	auto tIbo = createIBO(tIndices, tIndicesSize);
	tIbo->bind();

	tVao->unBind();

	return Model(tVao, tIbo->getIndicesCount());
}

int BasicLoader::readINT(std::ifstream * pInFile) {
	int temp = 0;
	pInFile->read((char*)&temp, sizeof(int));
	return temp;
}

void BasicLoader::readBuffer(std::ifstream * pInFile, void * pStream, unsigned int pBufferSize) {
	pInFile->read((char*)pStream, pBufferSize);
}

VertexArray * BasicLoader::createVAO() {
	auto tVao = VertexArray();
	mVaos.push_back(tVao);
	return &mVaos[mVaos.size() - 1];
}

VertexBuffer * BasicLoader::createVBO(const float * pData, unsigned int pSize) {
	auto tVbo = VertexBuffer(pData, pSize);
	mVbos.push_back(tVbo);
	return &mVbos[mVbos.size() - 1];
}

IndexBuffer * BasicLoader::createIBO(const int * pData, unsigned int pSize) {
	auto tIbo = IndexBuffer(pData, pSize);
	mIbos.push_back(tIbo);
	return &mIbos[mIbos.size() - 1];
}
