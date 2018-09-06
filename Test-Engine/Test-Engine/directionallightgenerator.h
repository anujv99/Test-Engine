#pragma once

#include <GLM/glm.hpp>

struct DirectionalLight {
	glm::vec3 mDirection;
	glm::vec3 mColor;

	DirectionalLight() :
		mDirection(glm::vec3(-1)), mColor(glm::vec3(1)) {}

	DirectionalLight(glm::vec3 pDirection, glm::vec3 pColor) :
		mDirection(pDirection), mColor(pColor) {}

};

class DirectionalLightGenerator {
public:
	static DirectionalLight createDirectionalLight(glm::vec3 pDirection, glm::vec3 pColor);
};

