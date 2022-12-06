#include "Sphere.h"

Sphere::Sphere(glm::vec3 cen, float rad)
: center(cen), radius(rad) {}

bool Sphere::hit(Ray& r, float tMin, float tMax, HitRecord& rec)
{
    glm::vec3 oc = r.origin() - center;
    auto a = glm::dot(r.direction(), r.direction());
    auto half_b = glm::dot(oc, r.direction());
    auto c = glm::dot(oc, oc) - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtDisc = sqrt(discriminant);

    auto root = (-half_b - sqrtDisc) / a;
    if (root < tMin || tMax < root) {
        root = (-half_b + sqrtDisc) / a;
        if (root < tMin || tMax < root)
            return false;
    }

    //setting values for hit record
    rec.t = root;
    rec.point = r.at(rec.t);
    glm::vec3 outwardNormal = (rec.point - center) / radius;
    rec.setFaceNormal(r, outwardNormal);

    return true;
}
