#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS 1000

class Input {
public:
	void setup(GLFWwindow * pWindow, unsigned int pWidth, unsigned int pHeight);
	void calculateIO();
	bool isKeyDown(int pKey);
	bool isKeyPressed(int pKey);
	void updateKeys();
public:
	bool isMousePosChanged() const { return mIsMousePosChanged; }
	inline double getMouseXPos() const { return mMouseXPos; }
	inline double getMouseYPos() const { return mMouseYPos; }
	inline double getMouseXOffset() const { return mMouseXOffset; }
	inline double getMouseYOffset() const { return mMouseYOffset; }
	inline bool isMouseEnabled() const { return mIsMouseEnabled; }
	inline double getDeltaTime() const { return mDeltaTime; }
private:
	double mMouseXPos;
	double mMouseYPos;
	bool mIsMousePosChanged;
	double mMouseXOffset;
	double mMouseYOffset;
	bool mIsMouseEnabled = true;
private:
	double mLastMouseXPos;
	double mLastMouseYPos;
private:
	double mLastFrameTime;
	double mDeltaTime;
private:
	GLFWwindow * mWindow;
	bool mKeyboardKeys[MAX_KEYS];
	unsigned int mWidth, mHeight;
	friend void cursor_pos_callback(GLFWwindow * pWindow, double pxPos, double pyPos);
private:
	void calculateMouseData();
	void checkWindowExitStatus();
};

