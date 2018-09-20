#pragma once

#include <string>

class Texture {
public:
	Texture();
	Texture(int pType);
	bool loadTexture(std::string pImageName);
	void bind() const { bind(0); }
	void bind(unsigned int pTextureUnit) const;
	void unBind() const;
	void setAnisotropicFiltering();
	void cleanUP();
private:
	unsigned int mTexID;
	int mTexType;
};
