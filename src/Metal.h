#pragma once

#include "Material.h"
#include <glm/glm.hpp>
#include "Ray.h"

class Metal : public Material {
public:
	Metal(glm::vec3& a);

	virtual bool scatter(
		Ray& r_in, HitRecord& rec, glm::vec3& attenuation, Ray& scattered
	) override;

private:
	glm::vec3 albedo;
};