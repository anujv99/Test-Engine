#include "watergenerator.h"

#include <vector>
#include <iostream>

Water WaterGenerator::addWater(unsigned int pVertexCount, unsigned int pSize) {
	float count = pVertexCount * pVertexCount;

	float * vertices = new float[count * 3];

	int vertexPointer = 0;
	for (unsigned int i = 0; i < pVertexCount; i++) {
		for (unsigned int j = 0; j < pVertexCount; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)pVertexCount - 1) * pSize;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)pVertexCount - 1) * pSize;
			vertexPointer++;
		}
	}

	std::vector<float> newVertices;
	newVertices.reserve(((count * 3) / 2) * 3);
	
	for (unsigned int gz = 0; gz < pVertexCount - 1; gz++) {
		for (unsigned int gx = 0; gx < pVertexCount - 1; gx++) {
			int topLeft = (gz*pVertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*pVertexCount) + gx;
			int bottomRight = bottomLeft + 1;

			newVertices.push_back(vertices[topLeft * 3]);
			newVertices.push_back(vertices[topLeft * 3 + 1]);
			newVertices.push_back(vertices[topLeft * 3 + 2]);

			newVertices.push_back(vertices[bottomLeft * 3]);
			newVertices.push_back(vertices[bottomLeft * 3 + 1]);
			newVertices.push_back(vertices[bottomLeft * 3 + 2]);

			newVertices.push_back(vertices[topRight * 3]);
			newVertices.push_back(vertices[topRight * 3 + 1]);
			newVertices.push_back(vertices[topRight * 3 + 2]);

			newVertices.push_back(vertices[topRight * 3]);
			newVertices.push_back(vertices[topRight * 3 + 1]);
			newVertices.push_back(vertices[topRight * 3 + 2]);

			newVertices.push_back(vertices[bottomRight * 3]);
			newVertices.push_back(vertices[bottomRight * 3 + 1]);
			newVertices.push_back(vertices[bottomRight * 3 + 2]);

			newVertices.push_back(vertices[bottomLeft * 3]);
			newVertices.push_back(vertices[bottomLeft * 3 + 1]);
			newVertices.push_back(vertices[bottomLeft * 3 + 2]);
		}
	}

	auto tVao = OpenGLResources::createVAO();
	tVao->bind();

	auto tVbo = OpenGLResources::createVBO(&newVertices[0], newVertices.size() * sizeof(float));
	tVbo->bind();
	tVao->addVertexBuffer(0, 3);
	tVbo->unBind();

	tVao->unBind();

	delete[] vertices;

	return Water(tVao, newVertices.size());
}
