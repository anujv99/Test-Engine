#include "Texture.h"

Texture::Texture() {
	glGenTextures(1, &mTexID);
	glBindTexture(GL_TEXTURE_2D, mTexID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

bool Texture::loadTexture(std::string pImageName) {
	bind();
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(pImageName.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		printf("TEXTURE::Failed to load texture : %s\n", pImageName.c_str());
		return false;
	}
	stbi_image_free(data);
	return true;
}

void Texture::bind(unsigned int pTextureUnit) const {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pTextureUnit);
}

void Texture::setAnisotropicFiltering() {
	bind();
	float tAmount = 4;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, tAmount);
	unBind();
}

void Texture::cleanUP() {
	glDeleteTextures(1, &mTexID);
}
