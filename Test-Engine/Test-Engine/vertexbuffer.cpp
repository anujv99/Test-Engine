#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(const void * pData, unsigned int pSize) {
	glGenBuffers(1, &mVertexBufferID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, pSize, pData, GL_STATIC_DRAW);
	unBind();
}

void VertexBuffer::cleanUP() {
	glDeleteBuffers(1, &mVertexBufferID);
}
