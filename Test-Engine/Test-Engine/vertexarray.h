#pragma once

#include "vertexbuffer.h"

class VertexArray {
public:
	VertexArray();
	void cleanUP();
	void addVertexBuffer(unsigned int pVertexAttribIndex, unsigned int pCoordinateSize);
	void bind() const;
	void unBind() const;
private:
	unsigned int mVertexArrayID;
};

