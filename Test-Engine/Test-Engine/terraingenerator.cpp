#include "terraingenerator.h"

Terrain TerrainGenerator::createTerrain(unsigned int pVertexCount, unsigned int pSize) {

	HeightsGenerator tHeightGenerator(1254544);

	int count = pVertexCount * pVertexCount;
	float * vertices = new float[count * 3];
	float * normals = new float[count * 3];
	float * textureCoords = new float[count * 2];
	int * indices = new int[6 * (pVertexCount - 1)*(pVertexCount - 1)];
	int vertexPointer = 0;
	for (unsigned int i = 0; i < pVertexCount; i++) {
		for (unsigned int j = 0; j < pVertexCount; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)pVertexCount - 1) * pSize;
			vertices[vertexPointer * 3 + 1] = getHeight(i, j, &tHeightGenerator);
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)pVertexCount - 1) * pSize;

			auto tNorm = calculateNormal(i, j, &tHeightGenerator);

			normals[vertexPointer * 3] = tNorm.x;
			normals[vertexPointer * 3 + 1] = tNorm.y;
			normals[vertexPointer * 3 + 2] = tNorm.z;

			textureCoords[vertexPointer * 2] = (float)j / ((float)pVertexCount - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)pVertexCount - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (unsigned int gz = 0; gz < pVertexCount - 1; gz++) {
		for (unsigned int gx = 0; gx < pVertexCount - 1; gx++) {
			int topLeft = (gz*pVertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*pVertexCount) + gx;
			int bottomRight = bottomLeft + 1;

			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomRight;
			indices[pointer++] = bottomLeft;
		}
	}

	auto tVao = OpenGLResources::createVAO();
	tVao->bind();

	auto tVbo = OpenGLResources::createVBO(vertices, count * 3 * sizeof(float));
	tVbo->bind();
	tVao->addVertexBuffer(0, 3);
	tVbo->unBind();

	tVbo = OpenGLResources::createVBO(normals, count * 3 * sizeof(float));
	tVbo->bind();
	tVao->addVertexBuffer(1, 3);
	tVbo->unBind();

	tVbo = OpenGLResources::createVBO(textureCoords, count * 2 * sizeof(float));
	tVbo->bind();
	tVao->addVertexBuffer(2, 2);
	tVbo->unBind();

	auto tIbo = OpenGLResources::createIBO(indices, sizeof(int) * (6 * (pVertexCount - 1)*(pVertexCount - 1)));
	tIbo->bind();

	tVao->unBind();

	delete[] vertices;
	delete[] normals;
	delete[] textureCoords;
	delete[] indices;

	return Terrain(tVao, tIbo->getIndicesCount());
}

glm::vec3 TerrainGenerator::calculateNormal(int x, int y, HeightsGenerator * pHeightsGenerator) {
	float heightL = getHeight(x - 1, y, pHeightsGenerator);
	float heightR = getHeight(x + 1, y, pHeightsGenerator);
	float heightD = getHeight(x, y - 1, pHeightsGenerator);
	float heightU = getHeight(x, y + 1, pHeightsGenerator);

	glm::vec3 sNorm(heightL - heightR, 2.0f, heightD - heightU);
	sNorm = glm::normalize(sNorm);
	return sNorm;
}

float TerrainGenerator::getHeight(int x, int y, HeightsGenerator * pHeightsGenerator) {
	return pHeightsGenerator->generateHeight(x, y);
}
