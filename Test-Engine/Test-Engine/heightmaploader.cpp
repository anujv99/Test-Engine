#include "heightmaploader.h"
#include "stb_image.h"

HeightmapLoader::HeightmapLoader(std::string pFileName, float pAmplitude) {
	AMPLITUDE = pAmplitude;
	pFileName = "res/textures/" + pFileName;
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(pFileName.c_str(), &width, &height, &nrChannels, 3);
	if (!data) {
		printf("TEXTURE::Failed to load texture : %s\n", pFileName.c_str());
		return;
	}
}

float HeightmapLoader::getHeight(int x, int y) {
	if (x < 0 || x > width || y < 0 || y > height)
		return 0;
	unsigned char * pixelOffset =  data + (x + height * y) * nrChannels;
	float tHeight = (float)pixelOffset[0];
	return (((tHeight / 255) * 2) - 1) * AMPLITUDE;
}

void HeightmapLoader::cleanUP() {
	stbi_image_free(data);
}
