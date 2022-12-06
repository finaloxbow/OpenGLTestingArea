#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

struct HitRecord {
	glm::vec3 point;
	glm::vec3 normal;
	float t;
	bool frontFace;

	inline void setFaceNormal(Ray& r, glm::vec3& outwardNormal) {
		frontFace = glm::dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) = 0;
};