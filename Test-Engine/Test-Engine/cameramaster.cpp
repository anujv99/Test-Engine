#include "cameramaster.h"

CameraMaster::CameraMaster() {}

void CameraMaster::updateCamera() {
	checkForMovement();
}

void CameraMaster::checkForMovement() {
	if (mInput->isKeyDown(GLFW_KEY_W)) {
		camera.ProcessKeyboard(FORWARD, (float)mInput->getDeltaTime());
	}
	if (mInput->isKeyDown(GLFW_KEY_S)) {
		camera.ProcessKeyboard(BACKWARD, (float)mInput->getDeltaTime());
	}
	if (mInput->isKeyDown(GLFW_KEY_A)) {
		camera.ProcessKeyboard(LEFT, (float)mInput->getDeltaTime());
	}
	if (mInput->isKeyDown(GLFW_KEY_D)) {
		camera.ProcessKeyboard(RIGHT, (float)mInput->getDeltaTime());
	}

	camera.ProcessMouseMovement((float)mInput->getMouseXOffset(), (float)mInput->getMouseYOffset());

}

CameraMaster::CameraMaster(Input * pInput) {
	mInput = pInput;
}
