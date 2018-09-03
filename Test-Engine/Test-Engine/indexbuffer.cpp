#include "indexbuffer.h"

IndexBuffer::IndexBuffer(const int * pData, unsigned int pSize) {
	glGenBuffers(1, &mIndexBufferID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pSize, pData, GL_STATIC_DRAW);
	unBind();
	mIndicesCount = pSize / sizeof(unsigned int);
}

void IndexBuffer::cleanUP() {
	glDeleteBuffers(1, &mIndexBufferID);
}

