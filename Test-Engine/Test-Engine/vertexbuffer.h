#pragma once

class VertexBuffer {
public:
	VertexBuffer(const void * pData, unsigned int pSize);
	void cleanUP();
	void bind() const;
	void unBind() const;
private:
	unsigned int mVertexBufferID;
};

