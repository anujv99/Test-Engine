#include "engine.h"

#define PAUSE system("PAUSE")

#include "shader.h"

int main() {
	Engine engine;
	int tStatus = engine.init();
	if (tStatus != 0) {
		PAUSE;
		return tStatus;
	}

	Shader shader("basic");

	engine.run();
	engine.destroy();
	
	PAUSE;
	return 0;
}