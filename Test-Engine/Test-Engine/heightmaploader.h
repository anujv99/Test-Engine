#pragma once

#include <string>
#include "stb_image.h"

class HeightmapLoader {
public:
	HeightmapLoader(std::string pFileName);
	float getHeight(int x, int y);
	void cleanUP();
private:
	float AMPLITUDE = 10.0f;
	unsigned char *data;
	int width, height, nrChannels;
};

