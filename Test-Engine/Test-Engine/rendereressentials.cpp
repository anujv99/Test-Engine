#include "rendereressentials.h"

#include <glad/glad.h>

void RendererEssentials::drawElements(unsigned int pVertexCount) {
	glDrawElements(GL_TRIANGLES, pVertexCount, GL_UNSIGNED_INT, 0);
}

void RendererEssentials::drawArrays(unsigned int pVertexCount) {
	glDrawArrays(GL_TRIANGLES, 0, pVertexCount);
}

void RendererEssentials::drawPoints(unsigned int pVertexCount) {
	glDrawArrays(GL_POINTS, 0, pVertexCount);
}

void RendererEssentials::enableVertexAttribArray(unsigned int pSize) {
	for (unsigned int i = 0; i <= pSize; i++) {
		glEnableVertexAttribArray(i);
	}
}
