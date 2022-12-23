#pragma once


#include "Ray.h"
#include "Hittable.h"

struct HitRecord;

class Material {
public:
	virtual bool scatter(
		Ray& r_in, HitRecord& rec, glm::vec3& attenuation, Ray& scattered
	) = 0;
};
