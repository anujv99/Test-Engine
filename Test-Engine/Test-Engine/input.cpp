#include "input.h"

void cursor_pos_callback(GLFWwindow * pWindow, double pxPos, double pyPos);

void Input::setup(GLFWwindow * pWindow, unsigned int pWidth, unsigned int pHeight) {
	mWindow = pWindow;
	mWidth = pWidth;
	mHeight = pHeight;
	glfwGetCursorPos(mWindow, &mMouseXPos, &mMouseYPos);
	mIsMousePosChanged = false;
	mLastMouseXPos = mMouseXPos;
	mLastMouseYPos = mMouseYPos;
	mMouseXOffset = 0;
	mMouseYOffset = 0;
	glfwSetWindowUserPointer(mWindow, (void*)(this));
	glfwSetCursorPosCallback(mWindow, cursor_pos_callback);

	mDeltaTime = 0.0;
	mLastFrameTime = 0.0;
}

void Input::calculateIO() {
	mDeltaTime = glfwGetTime() - mLastFrameTime;
	mLastFrameTime = glfwGetTime();
	checkWindowExitStatus();
	calculateMouseData();
}

bool Input::isKeyDown(int pKey) {
	return (glfwGetKey(mWindow, pKey) == GLFW_PRESS);
}

bool Input::isKeyPressed(int pKey) {
	return (isKeyDown(pKey) && !mKeyboardKeys[pKey]);
}

void Input::updateKeys() {
	for (int i = 0; i < MAX_KEYS; i++) {
		mKeyboardKeys[i] = isKeyDown(i);
	}
}

void Input::calculateMouseData() {
	mMouseXOffset = mMouseXPos - mLastMouseXPos;
	mMouseYOffset = mLastMouseYPos - mMouseYPos;
	if (mMouseXOffset != 0 || mMouseYOffset != 0) {
		mIsMousePosChanged = true;
	} else {
		mIsMousePosChanged = false;
	}
	mLastMouseXPos = mMouseXPos;
	mLastMouseYPos = mMouseYPos;

	if (isKeyPressed(GLFW_KEY_F2)) {
		if (mIsMouseEnabled)
			glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		mIsMouseEnabled = !mIsMouseEnabled;
	}

}

void Input::checkWindowExitStatus() {
	if (isKeyDown(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
}

void cursor_pos_callback(GLFWwindow * pWindow, double pxPos, double pyPos) {
	Input * tInput = (Input *)glfwGetWindowUserPointer(pWindow);
	tInput->mMouseXPos = pxPos;
	tInput->mMouseYPos = pyPos;
}
