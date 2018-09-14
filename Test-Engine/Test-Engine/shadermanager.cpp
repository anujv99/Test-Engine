#include "shadermanager.h"

std::map<SHADER_TYPES, Shader *> ShaderManager::mAllShaders;

Shader * ShaderManager::addShader(SHADER_TYPES pShaderType, std::string pShaderName) {
	Shader * tShader = new Shader(pShaderName);
	if (tShader->getStatus() != true) {
		printf("SHADER_MANAGER::Unable to create shader %s\n", pShaderName.c_str());
		return nullptr;
	}
	mAllShaders.insert(SHADER_PAIR(pShaderType, tShader));
	return getShader(pShaderType);
}

Shader * ShaderManager::getShader(SHADER_TYPES pShaderType) {
	Shader * temp;
	temp = mAllShaders.at(pShaderType);
	return temp;
}

void ShaderManager::cleanUP() {
	for (auto &sShader : mAllShaders) {
		sShader.second->cleanUP();
		delete(sShader.second);
	}
}
