#include "shader.h"

Shader::Shader(std::string pFileName) {
	std::string tFilePath = "res/shaders/" + pFileName + ".glsl";
	std::ifstream tInFile(tFilePath);

	if (!tInFile) {
		printf("SHADER::Failed to open file : %s\n", tFilePath.c_str());
		mShaderStatus = false;
		return;
	} else {
		createShaders(&tInFile);
		createShaderProgram();
	}
}

void Shader::cleanUP() {
	glDetachShader(mProgramID, mVertexShaderID);
	glDetachShader(mProgramID, mFragmentShaderID);
	glDeleteShader(mVertexShaderID);
	glDeleteShader(mFragmentShaderID);
	glDeleteProgram(mProgramID);
	printf("SHADER::Deleted successfully ( Program ID = %d )\n", mProgramID);
}

void Shader::createShaders(std::ifstream * pInFile) {
	GLenum tShaderType = 0;
	std::string tLine;

	std::string tShaderStirng;

	bool tIsFirst = true;
	bool tIsShader = false;

	while (std::getline(*pInFile, tLine)) {
		if ((tLine.find("//#")) != std::string::npos) {

			if (!tIsFirst) {
				tIsFirst = true;
			} else {
				if (tIsShader) {
					compileShader(tShaderStirng, tShaderType);
				}
			}

			if ((tLine.find("VERTEX")) != std::string::npos) {
				tShaderType = GL_VERTEX_SHADER;
				tShaderStirng.clear();
				tLine.clear();
				tIsShader = true;
			} else if ((tLine.find("FRAGMENT")) != std::string::npos) {
				tShaderType = GL_FRAGMENT_SHADER;
				tShaderStirng.clear();
				tLine.clear();
				tIsShader = true;
			} else if ((tLine.find("UNIFORMS")) != std::string::npos) {
				tIsShader = false;
			} else if ((tLine.find("END")) != std::string::npos) {
				tIsShader = false;
				break;
			}
		}
		tShaderStirng += tLine + "\n";
	}
}

void Shader::createShaderProgram() {
	mProgramID = glCreateProgram();
	glAttachShader(mProgramID, mVertexShaderID);
	glAttachShader(mProgramID, mFragmentShaderID);
	glLinkProgram(mProgramID);

	int tSuccess;
	char tInfoLog[512];

	glGetProgramiv(mProgramID, GL_LINK_STATUS, &tSuccess);
	if (!tSuccess) {
		glGetProgramInfoLog(mProgramID, 512, NULL, tInfoLog);
		printf("SHADER::Unable to create shader program : %s\n", tInfoLog);
		mShaderStatus = false;
	} else {
		printf("SHADER::Created successfully ( Program ID = %d )\n", mProgramID);
		loadUniforms();
	}
}

void Shader::loadUniforms() {
	bind();
	mUniformLocations[UNIFORM_MATRIX_MODEL] = getUniformLocation("model");
	mUniformLocations[UNIFORM_MATRIX_PROJECTION] = getUniformLocation("projection");
	mUniformLocations[UNIFORM_MATRIX_VIEW] = getUniformLocation("view");
	unBind();
}

void Shader::loadStoredUniform(glm::mat4 pValue, UNIFORM_LOCATIONS pLocation) {
	glUniformMatrix4fv(mUniformLocations[pLocation], 1, GL_FALSE, glm::value_ptr(pValue));
}

void Shader::compileShader(std::string pShaderString, GLenum pShaderType) {
	unsigned int tShaderID = glCreateShader(pShaderType);
	const char * tShaderSource = pShaderString.c_str();
	glShaderSource(tShaderID, 1, &tShaderSource, NULL);
	glCompileShader(tShaderID);

	int tSuccess;
	char tInfoLog[512];
	glGetShaderiv(tShaderID, GL_COMPILE_STATUS, &tSuccess);

	if (!tSuccess) {
		glGetShaderInfoLog(tShaderID, 512, NULL, tInfoLog);
		printf("SHADER::Unable to compile shader : %s\n", tInfoLog);
		mShaderStatus = false;
	}
	if (pShaderType == GL_VERTEX_SHADER) {
		mVertexShaderID = tShaderID;
	} else if (pShaderType == GL_FRAGMENT_SHADER) {
		mFragmentShaderID = tShaderID;
	}
}
