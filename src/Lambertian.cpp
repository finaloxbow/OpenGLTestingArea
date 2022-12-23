#include "Lambertian.h"
#include "Utils.h"

Lambertian::Lambertian(glm::vec3& a)
: albedo(a) {}

bool Lambertian::scatter(Ray& r_in, HitRecord& rec, glm::vec3& attenuation, Ray& scattered)
{
    auto scatter_direction = rec.normal + randomUnitVector();

    if (nearZero(scatter_direction))
        scatter_direction = rec.normal;


    scattered = Ray(rec.point, scatter_direction);
    attenuation = albedo;
    return true;
}
