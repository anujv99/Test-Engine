#pragma once
class RendererEssentials {
protected:
	void drawElements(unsigned int pVertexCount);
	void drawArrays(unsigned int pVertexCount);
	void drawPoints(unsigned int pVertexCount);
	void enableVertexAttribArray(unsigned int pSize);
	void drawInstancedElemets(unsigned int pVertexCount, unsigned int pInstances);
};

