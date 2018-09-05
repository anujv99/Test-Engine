#pragma once

#include <string>
#include <glad/glad.h>

#include "stb_image.h"

class Texture {
public:
	Texture();
	bool loadTexture(std::string pImageName);
	void bind() const { glBindTexture(GL_TEXTURE_2D, mTexID); }
	void bind(unsigned int pTextureUnit) const;
	void unBind() const { glBindTexture(GL_TEXTURE_2D, 0); }
	void setAnisotropicFiltering();
	void cleanUP();
private:
	unsigned int mTexID;
};
