#include "Camera.h"

Camera::Camera(float vFov, float aspectRatio)
{
    auto theta = degreesToRadians(vFov);
    auto h = tan(theta/2);
    auto viewportHeight = 2.0f  * h;
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
