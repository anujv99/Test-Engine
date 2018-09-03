#pragma once

#include "vertexbuffer.h"

class VertexArray {
public:
	VertexArray();
	void cleanUP();
	void addVertexBuffer(unsigned int pVertexAttribIndex, unsigned int pCoordinateSize);
	inline void bind() const { glBindVertexArray(mVertexArrayID); }
	inline void unBind() const { glBindVertexArray(0); }
private:
	unsigned int mVertexArrayID;
};

