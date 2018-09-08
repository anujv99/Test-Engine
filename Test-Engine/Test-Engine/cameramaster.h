#pragma once

#include "camera.h"
#include "input.h"

class CameraMaster {
public:
	CameraMaster(Input * pInput);
	CameraMaster();
	void updateCamera();
public:
	inline glm::mat4 getViewMatrix() { return camera.GetViewMatrix(); }
private:
	float mCameraSpeed = 5.0f;;
	Camera camera;
	void checkForMovement();
	Input * mInput;
};

