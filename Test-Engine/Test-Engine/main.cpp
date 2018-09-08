#include "engine.h"

#include "basicloader.h"

#define PAUSE system("PAUSE")

#define __MSAA__

int main() {
	Engine engine;
	int tStatus = engine.init();
	if (tStatus != 0) {
		PAUSE;
		return tStatus;
	}

	engine.run();
	engine.destroy();
	
	PAUSE;
	return 0;
}