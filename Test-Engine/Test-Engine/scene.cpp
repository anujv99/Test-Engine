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
