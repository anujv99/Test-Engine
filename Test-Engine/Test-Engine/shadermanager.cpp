#include "shadermanager.h"

std::map<SHADER_TYPES, Shader> ShaderManager::mAllShaders;

void ShaderManager::addShader(SHADER_TYPES pShaderType, std::string pShaderName) {
	Shader tShader(pShaderName);
	mAllShaders.insert(SHADER_PAIR(pShaderType, tShader));
}

const Shader * ShaderManager::getShader(SHADER_TYPES pShaderType) {
	Shader * temp;
	temp = &mAllShaders.at(pShaderType);
	return temp;
}

void ShaderManager::cleanUP() {
	for (auto &sShader : mAllShaders) {
		sShader.second.cleanUP();
	}
}
