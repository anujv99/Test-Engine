#pragma once

#include <string>
#include <fstream>

#include <glad/glad.h>

class Shader {
public:
	Shader(std::string pFileName);
	void cleanUP();
private:
	unsigned int mProgramID, mVertexShaderID, mFragmentShaderID;
	bool mShaderStatus = true;
private:
	void createShaders(std::ifstream * pInFile);
	void createShaderProgram();
	void compileShader(std::string pShaderString, GLenum pShaderType);
};
