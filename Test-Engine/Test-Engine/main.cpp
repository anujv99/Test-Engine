#include "engine.h"

#include "basicloader.h"

#define PAUSE system("PAUSE")

int main() {
	Engine engine;
	int tStatus = engine.init();
	if (tStatus != 0) {
		PAUSE;
		return tStatus;
	}

	auto rip = BasicLoader::loadModel("tree1");

	engine.run();
	engine.destroy();
	
	PAUSE;
	return 0;
}