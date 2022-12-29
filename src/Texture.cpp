#include "Texture.h"

SolidColor::SolidColor()
: colorValue(glm::vec3(0)) {}

SolidColor::SolidColor(glm::vec3 c)
: colorValue(c) {}

SolidColor::SolidColor(float red, float green, float blue)
: colorValue(glm::vec3(red, green, blue)) {}

glm::vec3 SolidColor::value(float u, float v, glm::vec3& p)
{
    return colorValue;
}
