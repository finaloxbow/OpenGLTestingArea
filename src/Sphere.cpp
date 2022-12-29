#include "Sphere.h"
#include "Utils.h"

Sphere::Sphere(glm::vec3 cen, float rad, Material* mat)
: center(cen), radius(rad), mat_ptr(mat) {}

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
    getSphereUV(outwardNormal, rec.u, rec.v);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool Sphere::boundingBox(float time0, float time1, AABB& outputBox)
{
    auto smaller = center - glm::vec3(radius, radius, radius);
    auto larger = center + glm::vec3(radius, radius, radius);

    outputBox = AABB(smaller, larger);

    return true;
}

void Sphere::getSphereUV(glm::vec3& p, float& u, float& v)
{
    auto theta = acos(-p.y);
    auto phi = atan2(-p.z, p.x) + pi;

    u = phi / (2 * pi);
    v = theta / pi;
}
