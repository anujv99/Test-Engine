#include "watergenerator.h"

#include <vector>
#include <iostream>

#include <glad/glad.h>

Water WaterGenerator::addWater(unsigned int pVertexCount, unsigned int pSize) {
	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	float count = (float)pVertexCount * (float)pVertexCount;

	float * vertices = new float[count * 2];

	int vertexPointer = 0;
	for (unsigned int i = 0; i < pVertexCount; i++) {
		for (unsigned int j = 0; j < pVertexCount; j++) {
			vertices[vertexPointer * 2] = (float)j / ((float)pVertexCount - 1) * pSize;
			vertices[vertexPointer * 2 + 1] = (float)i / ((float)pVertexCount - 1) * pSize;
			vertexPointer++;
		}
	}

	std::vector<float> newVertices;
	newVertices.reserve(((count * 2) / 2) * 3);
	std::vector<float> indicators;
	indicators.reserve(((count * 2) / 2) * 6);
	
	for (unsigned int gz = 0; gz < pVertexCount - 1; gz++) {
		for (unsigned int gx = 0; gx < pVertexCount - 1; gx++) {
			int topLeft = (gz*pVertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*pVertexCount) + gx;
			int bottomRight = bottomLeft + 1;

			newVertices.push_back(vertices[topLeft * 2]);
			newVertices.push_back(vertices[topLeft * 2 + 1]);

			indicators.push_back(vertices[topRight * 2]);
			indicators.push_back(vertices[topRight * 2 + 1]);
			indicators.push_back(vertices[bottomLeft * 2]);
			indicators.push_back(vertices[bottomLeft * 2 + 1]);

			newVertices.push_back(vertices[bottomLeft * 2]);
			newVertices.push_back(vertices[bottomLeft * 2 + 1]);

			indicators.push_back(vertices[topLeft * 2]);
			indicators.push_back(vertices[topLeft * 2 + 1]);
			indicators.push_back(vertices[topRight * 2]);
			indicators.push_back(vertices[topRight * 2 + 1]);

			newVertices.push_back(vertices[topRight * 2]);
			newVertices.push_back(vertices[topRight * 2 + 1]);

			indicators.push_back(vertices[bottomLeft * 2]);
			indicators.push_back(vertices[bottomLeft * 2 + 1]);
			indicators.push_back(vertices[topLeft * 2]);
			indicators.push_back(vertices[topLeft * 2 + 1]);

			newVertices.push_back(vertices[topRight * 2]);
			newVertices.push_back(vertices[topRight * 2 + 1]);

			indicators.push_back(vertices[bottomRight * 2]);
			indicators.push_back(vertices[bottomRight * 2 + 1]);
			indicators.push_back(vertices[bottomLeft * 2]);
			indicators.push_back(vertices[bottomLeft * 2 + 1]);

			newVertices.push_back(vertices[bottomLeft * 2]);
			newVertices.push_back(vertices[bottomLeft * 2 + 1]);

			indicators.push_back(vertices[topRight * 2]);
			indicators.push_back(vertices[topRight * 2 + 1]);
			indicators.push_back(vertices[bottomRight * 2]);
			indicators.push_back(vertices[bottomRight * 2 + 1]);

			newVertices.push_back(vertices[bottomRight * 2]);
			newVertices.push_back(vertices[bottomRight * 2 + 1]);

			indicators.push_back(vertices[bottomLeft * 2]);
			indicators.push_back(vertices[bottomLeft * 2 + 1]);
			indicators.push_back(vertices[topRight * 2]);
			indicators.push_back(vertices[topRight * 2 + 1]);
		}
	}

	auto tVao = OpenGLResources::createVAO();
	tVao->bind();

	auto tVbo = OpenGLResources::createVBO(&newVertices[0], newVertices.size() * sizeof(float));
	tVbo->bind();
	tVao->addVertexBuffer(0, 2);
	tVbo->unBind();

	tVbo = OpenGLResources::createVBO(&indicators[0], indicators.size() * sizeof(float));
	tVbo->bind();
	tVao->addVertexBuffer(1, 4);
	tVbo->unBind();

	tVao->unBind();

	delete[] vertices;

	//Change Height
	return Water(tVao, newVertices.size(), -8.0f);
}
