#include "HittableList.h"

HittableList::HittableList(){}

HittableList::HittableList(std::shared_ptr<Hittable> obj)
{
    add(obj);
}

void HittableList::clear()
{
    objectList.clear();
}

void HittableList::add(std::shared_ptr<Hittable> obj)
{
    objectList.push_back(obj);
}

bool HittableList::hit(Ray& r, float tMin, float tMax, HitRecord& rec)
{
    HitRecord tempRec;
    bool anyHit = false;
    auto closestHit = tMax;

    for (auto& obj : objectList) {
        if (obj->hit(r, tMin, closestHit, tempRec)) {
            anyHit = true;
            closestHit = tempRec.t;
            rec = tempRec;
        }
    }

    return anyHit;
}

bool HittableList::boundingBox(float time0, float time1, AABB& outputBox)
{
    if (objectList.empty()) return false;

    AABB tempBox;
    bool firstBox = true;

    for (auto& obj : objectList) {
        if (!obj->boundingBox(time0, time1, tempBox)) return false;
        outputBox = firstBox ? tempBox : AABB::surroundingBox(outputBox, tempBox);
        firstBox = false;
    }

    return true;
}
