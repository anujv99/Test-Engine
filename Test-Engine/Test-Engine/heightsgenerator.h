#pragma once

#include <cstdlib>
#include <iostream>

#include "perlinnoise.h"
#include "lualoader.h"

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
	static float AMPLiTUDE;
	static int OCTAVES;
	static float ROUGHNESS;
	int mSeed;
	FastNoise * mPerlinNoise;
};
