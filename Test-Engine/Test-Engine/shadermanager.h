#pragma once

#include <map>
#include "shader.h"

enum SHADER_TYPES {
	SHADER_BASIC
};

#define SHADER_PAIR std::pair<SHADER_TYPES, Shader>

class ShaderManager {
public:
	static void addShader(SHADER_TYPES pShaderType, std::string pShaderName);
	static const Shader * getShader(SHADER_TYPES pShaderType);
	static void cleanUP();
private:
	static std::map<SHADER_TYPES, Shader> mAllShaders;
};
