#pragma once

#include "Ray.h"
#include <glm/glm.hpp>
#include "Material.h"
#include "AABB.h"

class Material;

struct HitRecord {
	glm::vec3 point;
	glm::vec3 normal;
	Material* mat_ptr;
	float t;
	float u;
	float v;
	bool frontFace;

	inline void setFaceNormal(Ray& r, glm::vec3& outwardNormal) {
		frontFace = glm::dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) = 0;
	virtual bool boundingBox(float time0, float time1, AABB& outputBox) = 0;
};