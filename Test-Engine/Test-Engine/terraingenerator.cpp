#include "terraingenerator.h"

Terrain TerrainGenerator::createTerrain(unsigned int pVertexCount, unsigned int pSize) {
	PerlinNoise tPN(1);

	int count = pVertexCount * pVertexCount;
	float * vertices = new float[count * 3];
	float * normals = new float[count * 3];
	float * textureCoords = new float[count * 2];
	int * indices = new int[6 * (pVertexCount - 1)*(pVertexCount - 1)];
	int vertexPointer = 0;
	for (unsigned int i = 0; i < pVertexCount; i++) {
		for (unsigned int j = 0; j < pVertexCount; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)pVertexCount - 1) * pSize;
			auto temp = 2 * tPN.noise((double)i / (double)pSize, (double)j / (double)pSize, 0); //Height
			vertices[vertexPointer * 3 + 1] = (float)temp;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)pVertexCount - 1) * pSize;

			auto norm = calcluteNormal(i, j, pSize, tPN);
			normals[vertexPointer * 3] = norm.x;
			normals[vertexPointer * 3 + 1] = norm.y;
			normals[vertexPointer * 3 + 2] = norm.z;

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

glm::vec3 TerrainGenerator::calcluteNormal(int x, int y, int size, PerlinNoise pPN) {
	float heightL = 2 * (float)pPN.noise((double)(x - 1) / (double)size, (double)y / (double)size, 0);
	float heightR = 2 * (float)pPN.noise((double)(x + 1) / (double)size, (double)y / (double)size, 0);
	float heightD = 2 * (float)pPN.noise((double)x / (double)size, (double)(y - 1) / (double)size, 0);
	float heightU = 2 * (float)pPN.noise((double)x / (double)size, (double)(y + 1) / (double)size, 0);
	glm::vec3 norm(heightL - heightR, 0.2f, heightD - heightU);
	norm = glm::normalize(norm);
	return norm;
}
