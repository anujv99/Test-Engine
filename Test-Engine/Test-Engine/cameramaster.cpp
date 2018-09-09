#include "cameramaster.h"

CameraMaster::CameraMaster() {}

void CameraMaster::updateCamera() {
	checkForMovement();
}

void CameraMaster::checkForMovement() {

	if (mInput->isKeyDown(GLFW_KEY_W)) {
		camera.ProcessKeyboard(FORWARD, mCameraSpeed * (float)mInput->getDeltaTime());
	}
	if (mInput->isKeyDown(GLFW_KEY_S)) {
		camera.ProcessKeyboard(BACKWARD, mCameraSpeed * (float)mInput->getDeltaTime());
	}
	if (mInput->isKeyDown(GLFW_KEY_A)) {
		camera.ProcessKeyboard(LEFT, mCameraSpeed * (float)mInput->getDeltaTime());
	}
	if (mInput->isKeyDown(GLFW_KEY_D)) {
		camera.ProcessKeyboard(RIGHT, mCameraSpeed * (float)mInput->getDeltaTime());
	}

	if (!mInput->isMouseEnabled()) {
		camera.ProcessMouseMovement((float)mInput->getMouseXOffset(), (float)mInput->getMouseYOffset());
	}

}

CameraMaster::CameraMaster(Input * pInput) {
	mInput = pInput;
}
