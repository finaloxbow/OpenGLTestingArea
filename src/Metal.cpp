#include "Metal.h"

Metal::Metal(glm::vec3& a, float f)
: albedo(a), fuzz(f < 1 ? f : 1) {}

bool Metal::scatter(Ray& r_in, HitRecord& rec, glm::vec3& attenuation, Ray& scattered)
{
    auto reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
    scattered = Ray(rec.point, reflected + fuzz*randomInUnitSphere());
    attenuation = albedo;
    return glm::dot(scattered.direction(), rec.normal) > 0;
}
