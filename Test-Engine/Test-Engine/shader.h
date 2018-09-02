#pragma once

#include <string>
#include <fstream>

#include <glad/glad.h>

class Shader {
public:
	Shader(std::string pFileName);
	void cleanUP();
public:
	inline void bind() const { glUseProgram(mProgramID); }
	inline void unBind() const { glUseProgram(0); }
private:
	unsigned int mProgramID, mVertexShaderID, mFragmentShaderID;
	bool mShaderStatus = true;
private:
	void createShaders(std::ifstream * pInFile); 
	void compileShader(std::string pShaderString, GLenum pShaderType);
	void createShaderProgram();
};
