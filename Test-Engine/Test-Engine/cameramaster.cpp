#include "cameramaster.h"

#include "input.h"

CameraMaster::CameraMaster() {}

void CameraMaster::updateCamera() {
	checkForMovement();
}

void CameraMaster::checkForMovement() {

	if (Input::isKeyDown(GLFW_KEY_W)) {
		camera.ProcessKeyboard(FORWARD, mCameraSpeed * (float)Input::getDeltaTime());
	}
	if (Input::isKeyDown(GLFW_KEY_S)) {
		camera.ProcessKeyboard(BACKWARD, mCameraSpeed * (float)Input::getDeltaTime());
	}
	if (Input::isKeyDown(GLFW_KEY_A)) {
		camera.ProcessKeyboard(LEFT, mCameraSpeed * (float)Input::getDeltaTime());
	}
	if (Input::isKeyDown(GLFW_KEY_D)) {
		camera.ProcessKeyboard(RIGHT, mCameraSpeed * (float)Input::getDeltaTime());
	}

	if (!Input::isMouseEnabled()) {
		camera.ProcessMouseMovement((float)Input::getMouseXOffset(), (float)Input::getMouseYOffset());
	}

}
