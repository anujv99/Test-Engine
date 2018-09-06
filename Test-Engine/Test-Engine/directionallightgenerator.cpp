#include "directionallightgenerator.h"

DirectionalLight DirectionalLightGenerator::createDirectionalLight(glm::vec3 pDirection, glm::vec3 pColor) {
	return DirectionalLight(pDirection, pColor);
}
