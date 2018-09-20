#include "input.h"

#include "antialiasing.h"
#include <iostream>

double Input::mMouseXPos;
double Input::mMouseYPos;
bool Input::mIsMousePosChanged;
double Input::mMouseXOffset;
double Input::mMouseYOffset;
bool Input::mIsMouseEnabled;
bool Input::mIsWireframe;

double Input::mLastMouseXPos;
double Input::mLastMouseYPos;
double Input::mLastFrameTime;
double Input::mDeltaTime;
GLFWwindow * mWindow = nullptr;

bool Input::mKeyboardKeys[MAX_KEYS];
unsigned int Input::mWidth, Input::mHeight;

void cursor_pos_callback(GLFWwindow * pWindow, double pxPos, double pyPos) {
	Input::setMousePos(pxPos, pyPos);
}

void Input::setup(GLFWwindow * pWindow, unsigned int pWidth, unsigned int pHeight) {
	mIsMouseEnabled = true;
	mWindow = pWindow;
	mWidth = pWidth;
	mHeight = pHeight;
	glfwGetCursorPos(mWindow, &mMouseXPos, &mMouseYPos);
	mIsMousePosChanged = false;
	mLastMouseXPos = mMouseXPos;
	mLastMouseYPos = mMouseYPos;
	mMouseXOffset = 0;
	mMouseYOffset = 0;

	glfwSetCursorPosCallback(mWindow, cursor_pos_callback);

	mDeltaTime = 0.0;
	mLastFrameTime = 0.0;

	AntiAliasing::setWireframeBool(&mIsWireframe);
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

void Input::setMousePos(double pX, double pY) {
	mMouseXPos = pX;
	mMouseYPos = pY;
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

	if (isKeyPressed(GLFW_KEY_F3)) {
		if (mIsWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		mIsWireframe = !mIsWireframe;
	}

}

void Input::checkWindowExitStatus() {
	if (isKeyDown(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
}

