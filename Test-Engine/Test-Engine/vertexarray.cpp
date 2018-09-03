#include "vertexarray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &mVertexArrayID);
}

void VertexArray::cleanUP() {
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void VertexArray::addVertexBuffer(unsigned int pVertexAttribIndex, unsigned int pCoordinateSize) {
	glVertexAttribPointer(pVertexAttribIndex, pCoordinateSize, GL_FLOAT, GL_FLOAT, 0, (void*)0);
}
