#include "engine.h"

#include "collisioninterface.h"
#include <thread>
#include <chrono>

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
	CollisionInterface::createCollisionWorld();
	CollisionInterface::setGravity(glm::vec3(0, -9.8f, 0));

	mCamera = CameraMaster();
	mRenderer = MasterRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, &mCamera);
	mScenes = new SceneManager(&mAssetManager);

	glfwSwapInterval(0);

	printf("ENGINE::Initialized successfully!\n");
	return 0;
}

void Engine::run() {
	//Main Game Loop

	CollisionInterface::start();
	while (!mDisplay->shouldClose()) {
		Input::calculateIO();
		mCamera.updateCamera();

		Player::update();
		mRenderer.draw(mScenes->getActiveScene());

		Input::updateKeys();
		mDisplay->updateDisplay();
	}
	CollisionInterface::stop();
}

void Engine::destroy() {
	mAssetManager.cleanUP();
	mRenderer.cleanUP();
	OpenGLResources::cleanUP();
	ShaderManager::cleanUP();
	CollisionInterface::cleanUP();
	delete(mScenes);
	delete(mDisplay);
}
