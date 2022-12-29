#include "ImageTexture.h"

ImageTexture::ImageTexture()
: data(nullptr), width(0), height(0), bytesPerScanline(0) {}

ImageTexture::ImageTexture(const char* filename)
{

    int compPerPixel = bpp;
    data = stbi_load(filename, &width, &height, &compPerPixel, compPerPixel);

    if (!data) {
        printf("Error: could not load texture image file.\n");
        width = height = 0;
    }

    bytesPerScanline = bpp * width;
}

ImageTexture::~ImageTexture()
{
    delete data;
}

glm::vec3 ImageTexture::value(float u, float v, glm::vec3& p)
{
    //return cyan if no texture data
    if (data == nullptr) return glm::vec3(0.0f, 1.0f, 1.0f);

    u = clamp(u, 0.0f, 1.0f);
    v = 1.0f - clamp(v, 0.0f, 1.0f);
    auto i = static_cast<int>(u * width);
    auto j = static_cast<int>(v * height);

    if (i >= width) i = width - 1;
    if (j >= height) j = height - 1;

    const auto colorScale = 1.0f / 255.0f;
    auto pixel = data + (i + width * j) * bpp;

    return glm::vec3(colorScale*pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
}
