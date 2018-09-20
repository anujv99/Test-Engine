#pragma once

#include "camera.h"

class CameraMaster {
public:
	CameraMaster();
	void updateCamera();
public:
	inline glm::mat4 getViewMatrix() { return camera.GetViewMatrix(); }
	inline glm::mat4 getInvertedViewMatrix(float pHeight) { return camera.getInvertexViewMatrix(pHeight); }
	inline glm::vec3 getCameraPos() { return camera.Position; }
private:
	float mCameraSpeed = 15.0f;;
	Camera camera;
	void checkForMovement();
};

