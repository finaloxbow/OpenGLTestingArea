#pragma once

#include "Hittable.h"
#include "HittableList.h"

class BvhNode : public Hittable {
public:
	BvhNode();
	BvhNode(HittableList& list, float time0, float time1);
	BvhNode(std::vector<std::shared_ptr<Hittable>>& src_objects,
		size_t start, size_t end, float time0, float time1);

	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) override;
	virtual bool boundingBox(float time0, float time1, AABB& outputBox) override;

private:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	AABB box;
};