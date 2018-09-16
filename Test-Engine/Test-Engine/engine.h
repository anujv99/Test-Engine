#pragma once

#include "display.h"
#include "input.h"
#include "masterrenderer.h"
#include "shadermanager.h"
#include "cameramaster.h"

class Engine {
public:
	int init();
	void run();
	void destroy();
private:
	CameraMaster mCamera;
	AssetManager mAssetManager;
	SceneManager * mScenes;
	MasterRenderer mRenderer;
	Display * mDisplay;
};
