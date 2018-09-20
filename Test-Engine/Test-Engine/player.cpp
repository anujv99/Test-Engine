#include "player.h"

#include "input.h"

Model * Player::mPlayer = nullptr;
Terrain * Player::mTerrain = nullptr;
glm::vec3 Player::mVelocity = glm::vec3(0, 0, 0);

float vel = 20.0f;

void Player::setPlayer(Model * pPlayer, Terrain * pTerrain) {
	mPlayer = pPlayer;
	mPlayer->mRigidBody->setPosition(glm::vec3(10, 100, 10));
	mTerrain = pTerrain;
}

void Player::update() {

	if (Input::isKeyDown(GLFW_KEY_UP)) {
		mPlayer->mRigidBody->accelerate(glm::vec3(vel, 0, 0));
	} else if (Input::isKeyDown(GLFW_KEY_DOWN)) {
		mPlayer->mRigidBody->accelerate(glm::vec3(-vel, 0, 0));
	}

	if (Input::isKeyDown(GLFW_KEY_LEFT)) {
		mPlayer->mRigidBody->accelerate(glm::vec3(0, 0, -vel));
	} else if (Input::isKeyDown(GLFW_KEY_RIGHT)) {
		mPlayer->mRigidBody->accelerate(glm::vec3(0, 0, vel));
	}

}
