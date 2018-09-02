#include "display.h"

Display::Display(unsigned int pWidth, unsigned int pHeight) {
	if (!glfwInit()) {
		mStatus = false;
		printf("DISPLAY::Failed to initialize GLFW!\n");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mWindow = glfwCreateWindow(pWidth, pHeight, "Test Window", nullptr, nullptr);
	if (mWindow == nullptr) {
		printf("DISPLAY::Failed to create GLFW window\n");
		mStatus = false;
		return;
	}
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
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
