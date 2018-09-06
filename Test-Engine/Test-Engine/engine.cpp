#include "engine.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int Engine::init() {
	mDisplay = new Display(WINDOW_WIDTH, WINDOW_HEIGHT);
	bool tDisplayStatus = mDisplay->getStatus();
	if (!tDisplayStatus) {
		printf("ENGINE::Failed to create display\n");
		return -1;
	} else {
		printf("DISPLAY::GLFW window created successfuly\n");
		printf("DISPLAY::OpenGL Version %s\n", glGetString(GL_VERSION));
	}

	//Use GL functions after this line

	mInput.setup(mDisplay->getWindow(), WINDOW_WIDTH, WINDOW_HEIGHT);
	mRenderer = MasterRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	mScenes = new SceneManager(&mAssetManager);
	mCamera = CameraMaster(&mInput);

	glfwSwapInterval(0);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	printf("ENGINE::Initialized successfully!\n");
	return 0;
}

void Engine::run() {
	//Main Game Loop
	while (!mDisplay->shouldClose()) {
		mInput.calculateIO();
		mCamera.updateCamera();

		mRenderer.draw(mScenes->getActiveScene(), mCamera.getViewMatrix());

		mInput.updateKeys();
		mDisplay->updateDisplay();
	}
}

void Engine::destroy() {
	mRenderer.cleanUP();
	OpenGLResources::cleanUP();
	ShaderManager::cleanUP();
	delete(mScenes);
	delete(mDisplay);
}
