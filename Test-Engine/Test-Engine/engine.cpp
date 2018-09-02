#include "engine.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int Engine::init() {
	mDisplay = new Display(WINDOW_WIDTH, WINDOW_HEIGHT);
	bool tDisplayStatus = mDisplay->getStatus();
	if (!tDisplayStatus) {
		std::cout << "ENGINE::Failed to create display" << std::endl;
		return -1;
	} else {
		std::cout << "DISPLAY::GLFW window created successfuly." << std::endl;
		std::cout << "DISPLAY::OpenGL Version " << glGetString(GL_VERSION) << std::endl;
	}

	mInput.setup(mDisplay->getWindow(), WINDOW_WIDTH, WINDOW_HEIGHT);

	std::cout << "ENGINE::Initialized successfully!" << std::endl;
	return 0;
}

void Engine::run() {
	//Main Game Loop
	while (!mDisplay->shouldClose()) {
		mInput.calculateIO();



		mInput.updateKeys();
		mDisplay->updateDisplay();
	}
}

void Engine::destroy() {
	delete(mDisplay);
}
