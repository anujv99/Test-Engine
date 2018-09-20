#include "rigidbodystructure.h"

#include <GLM/gtc/matrix_transform.hpp>
#include "input.h"
#include <iostream>

RigidBodyStructure::RigidBodyStructure(glm::vec3 pPosition, glm::vec3 pRotation, float pScale, float pMass) {
	mModelMatrix = glm::mat4(1.0f);
	applyScale(pScale);
	applyTranslation(pPosition);
	applyRotation(pRotation);
}

void RigidBodyStructure::deaccelerate() {
	if (mVelocity.x > 0) {
		accelerate(glm::vec3(-mDeacceleration, 0, 0));
	} else if (mVelocity.x < 0) {
		accelerate(glm::vec3(mDeacceleration, 0, 0));
	}

	if (mVelocity.x < mVelocityBias && mVelocity.x > -mVelocityBias) {
		mVelocity.x = 0;
	}

	if (mVelocity.z > 0) {
		accelerate(glm::vec3(0, 0, -mDeacceleration));
	} else if (mVelocity.z < 0) {
		accelerate(glm::vec3(0, 0, mDeacceleration));
	}

	if (mVelocity.z < mVelocityBias && mVelocity.z > -mVelocityBias) {
		mVelocity.z = 0;
	}

}

void RigidBodyStructure::applyScale(float &pScale) {
	mModelMatrix = glm::scale(mModelMatrix, glm::vec3(pScale, pScale, pScale));
}

void RigidBodyStructure::applyRotation(glm::vec3 &pRotation) {
	mModelMatrix = glm::rotate(mModelMatrix, glm::radians(pRotation.x), glm::vec3(1, 0, 0));
	mModelMatrix = glm::rotate(mModelMatrix, glm::radians(pRotation.y), glm::vec3(0, 1, 0));
	mModelMatrix = glm::rotate(mModelMatrix, glm::radians(pRotation.z), glm::vec3(0, 0, 1));
}

void RigidBodyStructure::applyTranslation(glm::vec3 &pTranslation) {
	mModelMatrix = glm::translate(mModelMatrix, pTranslation);
}

void RigidBodyStructure::translate(glm::vec3 pPos) {
	applyTranslation(pPos);
}

void RigidBodyStructure::setPosition(glm::vec3 pPos) {
	mModelMatrix[3] = glm::vec4(pPos.x, pPos.y, pPos.z, 1.0f);
}

void RigidBodyStructure::accelerate(glm::vec3 pDir) {
	mVelocity += pDir;
	if (mVelocity.x > mMaxVelocity) {
		mVelocity.x = mMaxVelocity;
	} else if (mVelocity.x < -mMaxVelocity) {
		mVelocity.x = -mMaxVelocity;
	}
	if (mVelocity.z > mMaxVelocity) {
		mVelocity.z = mMaxVelocity;
	} else if (mVelocity.z < -mMaxVelocity) {
		mVelocity.z = -mMaxVelocity;
	}
}

void RigidBodyStructure::update() {
	deaccelerate();
	translate(mVelocity * (float)Input::getDeltaTime());
}

RigidBodyStructure::~RigidBodyStructure() {
}