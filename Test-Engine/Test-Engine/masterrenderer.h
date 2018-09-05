#pragma once

#include "basicmodelrenderer.h"
#include "scenemanager.h"
#include "shadermanager.h"

class MasterRenderer {
public:
	MasterRenderer() {}
	MasterRenderer(const unsigned int pWindowWidth, const unsigned int pWindowHeight);
	void draw(Scene * pScene, const glm::mat4 &mViewMat);
private:
	void clear();
private:
	glm::mat4 mProjection;
	BasicModelRenderer mBasicRenderer;
};

