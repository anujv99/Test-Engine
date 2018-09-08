#pragma once

#include <cstdlib>
#include <iostream>

#include "perlinnoise.h"

class HeightsGenerator {
public:
	HeightsGenerator(int pSeed);
	float generateHeight(int x, int y);
	void cleanUP() { delete(mPerlinNoise); }
private:
	float getNoise(int x, int y);
	float getSmoothNoise(int x, int y);
	float interpolate(float a, float b, float blend);
	float getInterpolatedNoise(float x, float y);
private:
	float AMPLiTUDE = 2.0f;
	int OCTAVES = 3;
	float ROUGHNESS = 0.3f;
	int mSeed;
	FastNoise * mPerlinNoise;
};
