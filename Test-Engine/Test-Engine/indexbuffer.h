#pragma once

class IndexBuffer {
public:
	IndexBuffer(const int * pData, unsigned int pSize);
	void cleanUP();
	void bind() const;
	void unBind() const;
	inline unsigned int getIndicesCount() const { return mIndicesCount; }
private:
	unsigned int mIndexBufferID;
	unsigned int mIndicesCount;
};
