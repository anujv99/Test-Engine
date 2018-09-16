#pragma once

#include <map>
#include "shader.h"

enum SHADER_TYPES {
	SHADER_BASIC,
	SHADER_TERRAIN,
	SHADER_FBO_QUAD,
	SHADER_WATER,
	SHADER_SKYBOX,
	SHADER_GRASS
};

#define SHADER_PAIR std::pair<SHADER_TYPES, Shader *>

class ShaderManager {
public:
	static Shader * addShader(SHADER_TYPES pShaderType, std::string pShaderName);
	static Shader * getShader(SHADER_TYPES pShaderType);
	static void cleanUP();
private:
	static std::map<SHADER_TYPES, Shader *> mAllShaders;
};
