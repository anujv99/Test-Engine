#pragma once

#include "basicmodelrenderer.h"
#include "scenemanager.h"
#include "shadermanager.h"
#include "terrainrenderer.h"
#include "antialiasing.h"
#include "waterrenderer.h"

class MasterRenderer {
public:
	MasterRenderer() {}
	MasterRenderer(const unsigned int pWindowWidth, const unsigned int pWindowHeight);
	void draw(Scene * pScene, const glm::mat4 &pViewMat);
	void cleanUP();
private:
	void clear();
private:
	void drawAssets(Scene * pScene, const glm::mat4 &pViewMat);
	glm::mat4 mProjection;
	BasicModelRenderer mBasicRenderer;
	TerrainRenderer mTerrainRenderer;
	WaterRenderer mWaterRenderer;
};

