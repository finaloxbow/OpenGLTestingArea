#pragma once
#include "Material.h"

class Dielectric : public Material {
public:
	Dielectric(float idx_of_refract);

	virtual bool scatter(
		Ray& r_in, HitRecord& rec, glm::vec3& attenuation, Ray& scattered
	) override;

private:
	float ir;

	static float reflectance(float cosine, float ref_idx) {
		//Schlick's Approximation for reflectance
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1-cosine), 5);
	}
};