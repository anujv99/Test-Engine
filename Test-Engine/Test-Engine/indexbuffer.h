#pragma once

#include <glad/glad.h>

class IndexBuffer {
public:
	IndexBuffer(const int * pData, unsigned int pSize);
	void cleanUP();
	inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID); }
	inline void unBind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	inline unsigned int getIndicesCount() const { return mIndicesCount; }
private:
	unsigned int mIndexBufferID;
	unsigned int mIndicesCount;
};
