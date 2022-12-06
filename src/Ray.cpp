#include "Ray.h"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
: orig(origin), dir(direction) {}

glm::vec3 Ray::origin()
{
    return orig;
}

glm::vec3 Ray::direction()
{
    return dir;
}

glm::vec3 Ray::at(double t) const
{
    return orig + glm::vec3(dir.x * t, dir.y * t, dir.z * t);
}

glm::vec3 Ray::ray_color() {
	auto t = hit_sphere(glm::vec3(0, 0, -1), 0.5f);
	if (t > 0) {
		glm::vec3 normal = glm::normalize(at(t) - glm::vec3(0, 0, -1));
		return 0.5f * (normal + glm::vec3(1, 1, 1));
	}

	glm::vec3 unit_direction = glm::normalize(dir);
	t = 0.5f * (unit_direction.y + 1.0f);
	//linear interpolation between the two colors
	return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
}

//converts an RGB vec3 to a uint_32 representing the RGBA value
//alpha always set to 1
unsigned int Ray::vec3ToRGBA(glm::vec3& pixel_color) {
	GLubyte red = static_cast<int>(255.999 * pixel_color.x);
	GLubyte green = static_cast<int>(255.999 * pixel_color.y);
	GLubyte blue = static_cast<int>(255.999 * pixel_color.z);
	GLubyte alpha = 0xff;

	//0x000000c1
	unsigned int finalColor = (red << 24) | (green << 16) | (blue << 8) | alpha;

	return finalColor;
}

float Ray::hit_sphere(const glm::vec3& center, float radius) {

	//checks whether ray is inside sphere
	glm::vec3 oc = orig - center;
	auto a = glm::dot(dir, dir);
	auto half_b = glm::dot(oc, dir);
	auto c = glm::dot(oc, oc) - radius * radius;

	auto discriminant = half_b*half_b - a*c;
	
	if (discriminant < 0)
		return -1.0f;
	else
		return (-half_b - sqrt(discriminant)) / a;
}