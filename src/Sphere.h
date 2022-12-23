#pragma once

#include "Hittable.h"
#include <glm/glm.hpp>
#include "Material.h"

class Sphere : public Hittable {
public:
	Sphere(glm::vec3 center, float radius, Material* mat);

	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) override;

private:
	glm::vec3 center;
	float radius;
	Material* mat_ptr;
};