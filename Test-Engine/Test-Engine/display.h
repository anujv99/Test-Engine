#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Display {
public:
	Display(unsigned int pWidth = DEFAULT_WIDTH, unsigned int pHeight = DEFAULT_HEIGHT);
	void updateDisplay();
	~Display();
public:
	inline bool getStatus() const { return mStatus; }
	inline GLFWwindow * getWindow() const { return mWindow; }
	bool shouldClose() { return glfwWindowShouldClose(mWindow); }
private:
	static const unsigned int DEFAULT_WIDTH = 1280;
	static const unsigned int DEFAULT_HEIGHT = 720;
	GLFWwindow * mWindow;
	bool mStatus = true;
};
