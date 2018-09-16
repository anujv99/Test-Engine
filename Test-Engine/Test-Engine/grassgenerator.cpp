#include "grassgenerator.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>

bool GrassGenerator::isModelGenerated = false;
VertexArray * GrassGenerator::mVAO = nullptr;
unsigned int GrassGenerator::mVertexCount = 0;

Grass GrassGenerator::generateGrass() {
	float vertices[] = {
		0.0f, 0.0f, 0.0f
	};

	auto tVao = OpenGLResources::createVAO();
	tVao->bind();

	auto tVbo = OpenGLResources::createVBO(vertices, sizeof(vertices));
	tVbo->bind();
	tVao->addVertexBuffer(0, 3);
	tVbo->unBind();
	tVao->unBind();

	return Grass(tVao, (sizeof(vertices) / sizeof(float)) / 3);

}
