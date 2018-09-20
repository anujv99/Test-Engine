#pragma once

#include <GLM/glm.hpp>

class RigidBodyStructure {
public:
	RigidBodyStructure(glm::vec3 pPosition = glm::vec3(0), glm::vec3 pRotation = glm::vec3(0), float pScale = 1.0f, float pMass = 0.0f);
	inline glm::mat4& getModelMatrix() { return mModelMatrix; }
	void translate(glm::vec3 pPos);
	void setPosition(glm::vec3 pPos);
	glm::vec3 getPosition() { return glm::vec3(mModelMatrix[3]); }
	void accelerate(glm::vec3 pDir);
	glm::vec3 * getVelocity() { return &mVelocity; }
	void update();
	~RigidBodyStructure();
private:
	void deaccelerate();
	void applyScale(float &pScale);
	void applyRotation(glm::vec3 &pRotation);
	void applyTranslation(glm::vec3 &pTranslation);
private:
	glm::mat4 mModelMatrix;
	glm::vec3 mVelocity = glm::vec3(0);
	float mAcceleration = 1.0f;
	float mMaxVelocity = 100.0f;
	float mDeacceleration = 0.5f;
	float mVelocityBias = 0.5f;
};
