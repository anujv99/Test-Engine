#include "collisionworld.h"

#include <thread>
#include <chrono>
#include <iostream>

#include "input.h"

#include <GLFW/glfw3.h>

#define FPS 120.0f

CollisionWorld::CollisionWorld() {}

CollisionWorld::~CollisionWorld() {
	for (auto collidor : mTerrains) {
		delete(collidor);
	}
	for (auto collidor : mRigidBodies) {
		delete(collidor);
	}
}

void CollisionWorld::update() {
	while (isActive) {
		updateRigidBodies();
		checkTerrainCollision();
		delay(1000 / FPS * 2.0);
	}
	isThreadFinished = true;
}

void CollisionWorld::startThread() {
	printf("COLLISION::New thread started\n");
	isActive = true;
	std::thread mThread(&CollisionWorld::update, this);
	mThread.detach();
}

void CollisionWorld::endThread() {
	isActive = false;
	printf("COLLISION::Thread destroyed\n");
}

void CollisionWorld::addTerrainCollidor(Terrain * pTerrain) {
	auto tTerr = new TerrainCollision(pTerrain);
	mTerrains.push_back(tTerr);
}

RigidBodyStructure * CollisionWorld::createRigidBody(glm::vec3 pPosition, glm::vec3 pRotation, float pScale, float pMass) {
	auto tRigibBody = new RigidBodyStructure(pPosition, pRotation, pScale, pMass);
	mRigidBodies.push_back(tRigibBody);
	return mRigidBodies.back();
}

void CollisionWorld::checkTerrainCollision() {
	for (auto terr : mTerrains) {
		for (RigidBodyStructure * rigidBody : mRigidBodies) {
			terr->checkCollision(rigidBody);
		}
	}
}

void CollisionWorld::updateRigidBodies() {
	for (auto rigidboy : mRigidBodies) {
		rigidboy->accelerate(mGravity);
		rigidboy->update();
	}
}

void CollisionWorld::delay(double timeInMillis) {
	double currentTime = glfwGetTime();
	while (true) {
		if (glfwGetTime() - currentTime > timeInMillis / 1000.0f) {
			break;
		}
	}
}
