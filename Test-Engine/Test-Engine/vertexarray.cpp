#include "vertexarray.h"

#include <glad/glad.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &mVertexArrayID);
}

void VertexArray::cleanUP() {
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void VertexArray::addVertexBuffer(unsigned int pVertexAttribIndex, unsigned int pCoordinateSize) {
	glVertexAttribPointer(pVertexAttribIndex, pCoordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void VertexArray::bind() const {
	glBindVertexArray(mVertexArrayID);
}

void VertexArray::unBind() const {
	glBindVertexArray(0);
}
