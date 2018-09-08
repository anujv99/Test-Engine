#include "scene.h"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::addModel(Model * pModel) {
	if (pModel != nullptr) {
		mModels.push_back(pModel);
	} else {
		printf("SCENE::Unable to add model to the scene\n");
	}
}

void Scene::addTerrain(Terrain * pTerrain) {
	if (pTerrain != nullptr) {
		mTerrains.push_back(pTerrain);
	} else {
		printf("SCENE::Unable to add terrain to the scene\n");
	}
}

void Scene::addSun(DirectionalLight * pSun) {
	if (pSun != nullptr) {
		mSun = pSun;
	} else {
		printf("SCENE::Unable to add sun\n");
	}
}

void Scene::addWater(Water * pWater) {
	if (pWater != nullptr) {
		mWaters.push_back(pWater);
	} else {
		printf("SCENE::Unable to add water to the scene\n");
	}
}
