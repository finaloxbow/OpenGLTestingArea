#pragma once

#include <memory>
#include <vector>

#include "Hittable.h"

class HittableList : public Hittable {
public:
	HittableList();

	HittableList(std::shared_ptr<Hittable> obj);

	void clear();

	void add(std::shared_ptr<Hittable> obj);

	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) override;
	virtual bool boundingBox(float time0, float time1, AABB& outputBox) override;

	std::vector<std::shared_ptr<Hittable>> objectList;
};