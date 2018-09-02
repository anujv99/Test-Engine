#pragma once

#include "display.h"
#include "input.h"

class Engine {
public:
	int init();
	void run();
	void destroy();
private:
	Display * mDisplay;
	Input mInput;
};
