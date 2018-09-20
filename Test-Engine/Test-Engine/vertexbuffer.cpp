#include "vertexbuffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void * pData, unsigned int pSize) {
	glGenBuffers(1, &mVertexBufferID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, pSize, pData, GL_STATIC_DRAW);
	unBind();
}

void VertexBuffer::cleanUP() {
	glDeleteBuffers(1, &mVertexBufferID);
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
}

void VertexBuffer::unBind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
