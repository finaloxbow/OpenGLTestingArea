#pragma once

#include "Material.h"
#include <glm/glm.hpp>

class Lambertian : public Material {
public:
	Lambertian(glm::vec3& a);

	virtual bool scatter(
		Ray& r_in, HitRecord& rec, glm::vec3& attenuation, Ray& scattered
	) override;

private:
	glm::vec3 albedo;
};