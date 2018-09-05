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
	UNIFORM_MATRIX_VIEW
};

class Shader {
public:
	Shader(std::string pFileName);
	void cleanUP();
public:
	void loadStoredUniform(glm::mat4 pValue, UNIFORM_LOCATIONS pLocation);
public:
	inline void bind() const { glUseProgram(mProgramID); }
	inline void unBind() const { glUseProgram(0); }
	inline bool getStatus() const { return mShaderStatus; }
	inline unsigned int getUniformLocation(std::string pUniformName) const { return glGetUniformLocation(mProgramID, pUniformName.c_str()); }
private:
	unsigned int mProgramID, mVertexShaderID, mFragmentShaderID;
	bool mShaderStatus = true;
	unsigned int mUniformLocations[3];
private:
	void createShaders(std::ifstream * pInFile);
	void compileShader(std::string pShaderString, GLenum pShaderType);
	void createShaderProgram();
	void loadUniforms();
};
