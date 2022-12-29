#pragma once

#include "Material.h"
#include "Texture.h"
#include <glm/glm.hpp>

class Lambertian : public Material {
public:
	Lambertian(glm::vec3& a);
	Lambertian(std::shared_ptr<Texture> a);

	virtual bool scatter(
		Ray& r_in, HitRecord& rec, glm::vec3& attenuation, Ray& scattered
	) override;

private:
	std::shared_ptr<Texture> albedo;
};