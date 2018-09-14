#pragma once

#include "basicmodelrenderer.h"
#include "scenemanager.h"
#include "shadermanager.h"
#include "terrainrenderer.h"
#include "antialiasing.h"
#include "waterrenderer.h"
#include "cameramaster.h"
#include "skyboxrenderer.h"

class MasterRenderer {
public:
	MasterRenderer() {}
	MasterRenderer(const unsigned int pWindowWidth, const unsigned int pWindowHeight, CameraMaster * pCamera);
	void draw(Scene * pScene);
	void cleanUP();
private:
	void clear();
	void processAndRenderWater(Scene * pScene, const glm::mat4 &pViewMat);
	void setClipPlane(Shader * pShader, glm::vec4 pValue);
	void drawAssets(Scene * pScene, const glm::mat4 &pViewMat);
	void setSun(DirectionalLight * pSun, Shader * pShader);
private:
	CameraMaster * mCamera;
	glm::mat4 mProjection;
	BasicModelRenderer mBasicRenderer;
	TerrainRenderer mTerrainRenderer;
	WaterRenderer mWaterRenderer;
	WaterFBOs mWaterFbos;
	SkyboxRenderer mSkyboxRenderer;
};

