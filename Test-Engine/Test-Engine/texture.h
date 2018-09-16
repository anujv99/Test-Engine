#pragma once

#include <string>
#include <glad/glad.h>

#include "stb_image.h"

class Texture {
public:
	Texture();
	Texture(GLenum pType);
	bool loadTexture(std::string pImageName);
	void bind() const { bind(0); }
	void bind(unsigned int pTextureUnit) const;
	void unBind() const { glBindTexture(mTexType, 0); }
	void setAnisotropicFiltering();
	void cleanUP();
private:
	unsigned int mTexID;
	GLenum mTexType;
};
