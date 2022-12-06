#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Ray {
public:
	Ray(const glm::vec3& origin, const glm::vec3& direction);

	glm::vec3 origin();

	glm::vec3 direction();

	glm::vec3 at(double t) const;

	glm::vec3 ray_color();

	float hit_sphere(const glm::vec3& center, float radius);

	static unsigned int vec3ToRGBA(glm::vec3& pixel_color);

private:
	glm::vec3 orig, dir;
};