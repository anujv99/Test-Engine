#pragma once

#include <GLFW/glfw3.h>

#define MAX_KEYS 1000

class Input {
public:
	static void setup(GLFWwindow * pWindow, unsigned int pWidth, unsigned int pHeight);
	static void calculateIO();
	static bool isKeyDown(int pKey);
	static bool isKeyPressed(int pKey);
	static void updateKeys();
public:
	static bool isMousePosChanged() { return mIsMousePosChanged; }
	static inline double getMouseXPos() { return mMouseXPos; }
	static inline double getMouseYPos() { return mMouseYPos; }
	static inline double getMouseXOffset() { return mMouseXOffset; }
	static inline double getMouseYOffset() { return mMouseYOffset; }
	static inline bool isMouseEnabled() { return mIsMouseEnabled; }
	static inline double getDeltaTime() { return mDeltaTime; }
public:
	static void setMousePos(double pX, double pY);
private:
	static double mMouseXPos;
	static double mMouseYPos;
	static bool mIsMousePosChanged;
	static double mMouseXOffset;
	static double mMouseYOffset;
	static bool mIsMouseEnabled;
	static bool mIsWireframe;
private:
	static double mLastMouseXPos;
	static double mLastMouseYPos;
private:
	static double mLastFrameTime;
	static double mDeltaTime;
private:
	static bool mKeyboardKeys[MAX_KEYS];
	static unsigned int mWidth, mHeight;
private:
	static void calculateMouseData();
	static void checkWindowExitStatus();
};

