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

	Input::setup(mDisplay->getWindow(), WINDOW_WIDTH, WINDOW_HEIGHT);

	mCamera = CameraMaster();
	mRenderer = MasterRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, &mCamera);
	mScenes = new SceneManager(&mAssetManager);

	printf("ENGINE::Initialized successfully!\n");
	return 0;
}

void Engine::run() {
	//Main Game Loop
	while (!mDisplay->shouldClose()) {
		Input::calculateIO();
		mCamera.updateCamera();

		mRenderer.draw(mScenes->getActiveScene());

		Input::updateKeys();
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
