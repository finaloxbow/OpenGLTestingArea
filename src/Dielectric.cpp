#include "Dielectric.h"

Dielectric::Dielectric(float idx_of_refract)
: ir(idx_of_refract) {}

bool Dielectric::scatter(Ray& r_in, HitRecord& rec, glm::vec3& attenuation, Ray& scattered)
{
    attenuation = glm::vec3(1.0f, 1.0f, 1.0f);
    float refract_ratio = rec.frontFace ? (1.0f / ir) : ir;

    glm::vec3 unitDir = glm::normalize(r_in.direction());
    float cos_theta = fmin(glm::dot(-unitDir, rec.normal), 1.0f);
    float sin_theta = sqrt(1.0f - cos_theta*cos_theta);

    bool cannot_refract = refract_ratio * sin_theta > 1.0f;
    glm::vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refract_ratio) > randomFloat())
        direction = reflect(unitDir, rec.normal);
    else
        direction = refract(unitDir, rec.normal, refract_ratio);

    scattered = Ray(rec.point, direction);
    return true;
}
