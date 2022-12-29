#include "bvhNode.h"

BvhNode::BvhNode()
: left(nullptr), right(nullptr) {}

BvhNode::BvhNode(HittableList& list, float time0, float time1)
: BvhNode(list.objectList, 0, list.objectList.size(), time0, time1) {}

bool boxCompare(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b, int axis) {
    AABB boxA;
    AABB boxB;

    if (!a->boundingBox(0, 0, boxA) || !b->boundingBox(0, 0, boxB))
        printf("No bounding box in bvh node constructor.\n");

    return boxA.min()[axis] < boxB.min()[axis];
}

bool box_x_compare(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
    return boxCompare(a, b, 0);
}

bool box_y_compare(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
    return boxCompare(a, b, 1);
}

bool box_z_compare(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
    return boxCompare(a, b, 2);
}

BvhNode::BvhNode(std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end, float time0, float time1)
{
    auto objects = src_objects;

    int axis = randomInt(0, 2);
    auto comparator = 
          (axis == 0) ? box_x_compare
        : (axis == 1) ? box_y_compare
        : box_z_compare;

    size_t objectSpan = end - start;

    if (objectSpan == 1) {
        left = right = objects[start];
    }
    else if (objectSpan == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            left = objects[start];
            right = objects[start + 1];
        }
        else {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + objectSpan / 2;
        left = std::make_shared<BvhNode>(objects, start, mid, time0, time1);
        right = std::make_shared<BvhNode>(objects, mid, end, time0, time1);
    }

    AABB boxLeft, boxRight;

    if ( !left->boundingBox(time0, time1, boxLeft)
        || !right->boundingBox(time0, time1, boxRight))
        printf("No bounding box in bvh node constructor.\n");

    box = AABB::surroundingBox(boxLeft, boxRight);
}

bool BvhNode::hit(Ray& r, float tMin, float tMax, HitRecord& rec)
{
    if (!box.hit(r, tMin, tMax)) return false;

    bool hitLeft = left->hit(r, tMin, tMax, rec);
    bool hitRight = right->hit(r, tMin, tMax, rec);

    return hitLeft || hitRight;
}

bool BvhNode::boundingBox(float time0, float time1, AABB& outputBox)
{
    outputBox = box;
    return true;
}
