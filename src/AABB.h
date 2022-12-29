#pragma once

#include <glm/glm.hpp>
#include "Ray.h"

class AABB {
public:
	AABB() : minimum(glm::vec3(0)), maximum(glm::vec3(0)) {}
	AABB(glm::vec3& a, glm::vec3& b) : minimum(a), maximum(b) {}

	glm::vec3 min() { return minimum; }
	glm::vec3 max() { return maximum; }

	bool hit(Ray& r, float tMin, float tMax) {
		for (int a = 0; a < 3; a++) {
			auto invD = 1.0f / r.direction()[a];
			auto t0 = (min()[a] - r.origin()[a]) * invD;
			auto t1 = (max()[a] - r.origin()[a]) * invD;
			if (invD < 0.0f)
				std::swap(t0, t1);
			tMin = t0 > tMin ? t0 : tMin;
			tMax = t1 < tMax ? t1 : tMax;
			if (tMax <= tMin)
				return false;
		}

		return true;
	}

	static AABB surroundingBox(AABB box0, AABB box1) {
		glm::vec3 smaller(fmin(box0.min().x, box1.min().x),
			fmin(box0.min().y, box1.min().y),
			fmin(box0.min().z, box1.min().z));
		glm::vec3 bigger(fmax(box0.max().x, box1.max().x),
			fmax(box0.max().y, box1.max().y),
			fmax(box0.max().z, box1.max().z));

		return AABB(smaller, bigger);
	}

private:
	glm::vec3 minimum;
	glm::vec3 maximum;
};