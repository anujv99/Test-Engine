#include "display.h"

Display::Display(unsigned int pWidth, unsigned int pHeight) {
	if (!glfwInit()) {
		mStatus = false;
		std::cout << "DISPLAY::Failed to initialize GLFW!" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mWindow = glfwCreateWindow(pWidth, pHeight, "Test Window", nullptr, nullptr);
	if (mWindow == nullptr) {
		std::cout << "DISPLAY::Failed to create GLFW window" << std::endl;
		mStatus = false;
		return;
	}
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		mStatus = false;
		return;
	}

	glViewport(0, 0, pWidth, pHeight);

}

void Display::updateDisplay() {
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

Display::~Display() {
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}
