#include "Camera.h"

Camera::Camera(
    glm::vec3 lookFrom,
    glm::vec3 lookAt,
    glm::vec3 vup, 
    float vFov, 
    float aspectRatio,
    float aperture,
    float focusDist)
{
    auto theta = degreesToRadians(vFov);
    auto h = tan(theta/2);
    auto viewportHeight = 2.0f  * h;
    auto viewportWidth = aspectRatio * viewportHeight;
    
    w = glm::normalize(lookFrom - lookAt);
    u = glm::normalize(glm::cross(vup, w));
    v = glm::cross(w, u);

    origin = lookFrom;
    horizontal = focusDist * viewportWidth * u;
    vertical = focusDist * viewportHeight * v;
    lowerLeftCorner = origin - (horizontal / 2.0f) 
        - (vertical / 2.0f) - focusDist * w;

    lensRadius = aperture / 2.0f;
}

Ray Camera::getRay(float s, float t)
{
    glm::vec3 rd = lensRadius * randomInUnitDisk();
    glm::vec3 offset = u * rd.x + v * rd.y;

    return Ray(
        origin + offset,
        lowerLeftCorner + s*horizontal + t*vertical - origin - offset
    );
}
