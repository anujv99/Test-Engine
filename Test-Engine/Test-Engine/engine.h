#pragma once

#include "display.h"
#include "input.h"
#include "shadermanager.h"

class Engine {
public:
	int init();
	void run();
	void destroy();
private:
	Display * mDisplay;
	Input mInput;
};
