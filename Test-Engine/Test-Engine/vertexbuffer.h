#pragma once

#include <glad/glad.h>

class VertexBuffer {
public:
	VertexBuffer(const void * pData, unsigned int pSize);
	void cleanUP();
	inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID); }
	inline void unBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
private:
	unsigned int mVertexBufferID;
};

