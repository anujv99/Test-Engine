#include "heightsgenerator.h"

#define PI 3.141592653589793

HeightsGenerator::HeightsGenerator(int pSeed) {
	mSeed = pSeed;
	mPerlinNoise = new FastNoise(pSeed);
}

float HeightsGenerator::generateHeight(int x, int y) {
	float total = 0;
	float d = (float)std::pow(2, OCTAVES - 1);
	for (int i = 0; i < OCTAVES; i++) {
		float freq = (float)(std::pow(2, i) / d);
		float amp = (float)std::pow(ROUGHNESS, i) * AMPLiTUDE;
		total += getInterpolatedNoise(x * freq, y * freq) * amp;
	}
	return total;
}

float HeightsGenerator::getNoise(int x, int y) {
	float tHeight = mPerlinNoise->GetPerlin(x * 1252, y * 5423);
	tHeight *= 10;
	return tHeight;
}

float HeightsGenerator::getSmoothNoise(int x, int y) {
	float tCorners = (getNoise(x - 1, y - 1) + getNoise(x + 1, y - 1) + getNoise(x + 1, y + 1) + getNoise(x - 1, y + 1)) / 16.0f;
	float tSides = (getNoise(x - 1, y) + getNoise(x + 1, y) + getNoise(x, y + 1) + getNoise(x, y - 1)) / 8.0f;
	float tCenter = getNoise(x, y) / 4.0f;
	return tCenter + tSides + tCorners;
}

float HeightsGenerator::interpolate(float a, float b, float blend) {
	double theta = blend * PI;
	float f = (float)(1.0f - std::cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

float HeightsGenerator::getInterpolatedNoise(float x, float y) {
	int intX = (int)x;
	int intY = (int)y;
	float fracX = x - intX;
	float fracY = y - intY;

	float v1 = getSmoothNoise(intX, intY);
	float v2 = getSmoothNoise(intX + 1, intY);
	float v3 = getSmoothNoise(intX, intY + 1);
	float v4 = getSmoothNoise(intX + 1, intY + 1);
	float i1 = interpolate(v1, v2, fracX);
	float i2 = interpolate(v3, v4, fracX);
	return interpolate(i1, i2, fracY);
}

