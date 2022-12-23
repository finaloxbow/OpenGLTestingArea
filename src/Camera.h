#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

class Camera {
public:
	Camera(float vfov, float aspectRatio);

	Ray getRay(float u, float v);

private:
	glm::vec3 origin;
	glm::vec3 lowerLeftCorner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
};