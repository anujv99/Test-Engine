#pragma once

#include <string>
#include <fstream>

#include <glad/glad.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

enum UNIFORM_LOCATIONS {
	UNIFORM_MATRIX_MODEL,
	UNIFORM_MATRIX_PROJECTION,
	UNIFORM_MATRIX_VIEW,
	UNIFORM_SUN_DIRECTION,
	UNIFORM_SUN_COLOR,
	UNIFORM_CLIP_PLANE,
	UNIFORM_WATER_HEIGHT,
	UNIFORM_CAMERA_POSITION
};

class Shader {
public:
	Shader(std::string pFileName);
	void cleanUP();
public:
	void setInt(int pValue, std::string pName);
	void setFloat(float pValue, std::string pName);
public:
	void loadStoredUniform(glm::mat4 pValue, UNIFORM_LOCATIONS pLocation);
	void loadStoredUniform(glm::vec4 pValue, UNIFORM_LOCATIONS pLocation);
	void loadStoredUniform(glm::vec3 pValue, UNIFORM_LOCATIONS pLocation);
	void loadStoredUniform(float pValue, UNIFORM_LOCATIONS pLocation);
public:
	inline void bind() const { glUseProgram(mProgramID); }
	inline void unBind() const { glUseProgram(0); }
	inline bool getStatus() const { return mShaderStatus; }
	inline unsigned int getUniformLocation(std::string pUniformName) const { return glGetUniformLocation(mProgramID, pUniformName.c_str()); }
private:
	unsigned int mProgramID, mVertexShaderID, mGeometryShader = -1, mFragmentShaderID;
	bool mShaderStatus = true;
	unsigned int mUniformLocations[10];
private:
	void createShaders(std::ifstream * pInFile);
	void compileShader(std::string pShaderString, GLenum pShaderType);
	void createShaderProgram();
	void loadUniforms();
};
