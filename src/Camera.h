#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

class Camera {
public:
	Camera(unsigned int scrWidth, unsigned int scrHeight);

	Ray getRay(float u, float v);

private:
	unsigned int scrWidth;
	unsigned int scrHeight;
	glm::vec3 origin;
	glm::vec3 lowerLeftCorner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
};