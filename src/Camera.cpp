#include "Camera.h"

Camera::Camera(unsigned int width, unsigned int height)
: scrWidth(width), scrHeight(height) {
    auto aspectRatio = 16.0f / 9.0f;
    auto viewportHeight = 2.0f;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0f;

    origin = glm::vec3(0,0,0);
    horizontal = glm::vec3(viewportWidth, 0, 0);
    vertical = glm::vec3(0, viewportHeight, 0);
    lowerLeftCorner = origin - (horizontal / 2.0f)
        - (vertical / 2.0f) - glm::vec3(0, 0, focalLength);
}

Ray Camera::getRay(float u, float v)
{
    return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
}
