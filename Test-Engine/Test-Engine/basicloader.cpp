#include "basicloader.h"

std::list<VertexArray> BasicLoader::mVaos;
std::list<VertexBuffer> BasicLoader::mVbos;
std::list<IndexBuffer> BasicLoader::mIbos;
std::list<Texture> BasicLoader::mTextures;

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
	tVao->addVertexBuffer(1, 3);
	tVbo->unBind();

	tVbo = createVBO(tTexCoords, tTexCoordsSize);
	tVbo->bind();
	tVao->addVertexBuffer(2, 2);
	tVbo->unBind();


	auto tIbo = createIBO(tIndices, tIndicesSize);
	tIbo->bind();

	tVao->unBind();

	delete[] tVertices;
	delete[] tNormals;
	delete[] tTexCoords;
	delete[] tIndices;

	auto tFinalModel =  Model(tVao, tIbo->getIndicesCount());
	auto tTex = createTexture();
	bool status = tTex->loadTexture("res/models/" + pFilePath + ".jpg");
	if (!status) {
		printf("LOADER::Texture for model : %s : not found\n", pFilePath.c_str());
		tFinalModel.mDiffuseTex = nullptr;
	} else {
		tFinalModel.mDiffuseTex = tTex;
	}

	return tFinalModel;
}

void BasicLoader::cleanUP() {
	for (auto &sBuffer : mIbos) {
		sBuffer.cleanUP();
	}
	for (auto &sBuffer : mVbos) {
		sBuffer.cleanUP();
	}
	for (auto &sVAO : mVaos) {
		sVAO.cleanUP();
	}
	for (auto &sTex : mTextures) {
		sTex.cleanUP();
	}
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
	return &mVaos.back();
}

VertexBuffer * BasicLoader::createVBO(const float * pData, unsigned int pSize) {
	auto tVbo = VertexBuffer(pData, pSize);
	mVbos.push_back(tVbo);
	return &mVbos.back();
}

IndexBuffer * BasicLoader::createIBO(const int * pData, unsigned int pSize) {
	auto tIbo = IndexBuffer(pData, pSize);
	mIbos.push_back(tIbo);
	return &mIbos.back();
}

Texture * BasicLoader::createTexture() {
	auto tTexture = Texture();
	mTextures.push_back(tTexture);
	return &mTextures.back();
}
