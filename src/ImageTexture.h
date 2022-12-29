#pragma once

#include "Texture.h"
#include "Utils.h"
#include "../vendor/stb/stb_image.h"

class ImageTexture : public Texture {
public:
	const static int bpp = 3;

	ImageTexture();
	ImageTexture(const char* filename);
	~ImageTexture();

	virtual glm::vec3 value(float u, float v, glm::vec3& p) override;

private:
	unsigned char* data;
	int width, height;
	int bytesPerScanline;
};