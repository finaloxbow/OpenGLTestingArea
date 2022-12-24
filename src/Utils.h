#pragma once

#include <limits>
#include <random>
#include <glm/glm.hpp>

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415927f;

inline float degreesToRadians(float degrees) {
	return degrees * pi / 180.0f;
}

inline float randomFloat() {
	static std::uniform_real_distribution<float> distr(0.0f, 1.0f);
	static std::mt19937 gen;
	return distr(gen);
}

inline float randomFloat(float min, float max) {
	return min + (max - min) * randomFloat();
}

inline float clamp(float x, float min, float max) {
	if (x < min) return min;
	if (x > max) return max;

	return x;
}

inline static glm::vec3 random() {
	return glm::vec3(randomFloat(), randomFloat(), randomFloat());
}

inline static glm::vec3 random(float min, float max) {
	return glm::vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}

static glm::vec3 randomInUnitSphere() {
	while (true) {
		auto p = random(-1, 1);
		if (glm::dot(p, p) >= 1) continue;
		return p;
	}
}

static glm::vec3 randomUnitVector() {
	return glm::normalize(randomInUnitSphere());
}

static bool nearZero(glm::vec3& v) {
	const auto s = 1e-8;
	return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s);
}

static glm::vec3 reflect(glm::vec3& v, glm::vec3& n) {
	return v - 2.0f * glm::dot(v, n) * n;
}

static float length_squared(glm::vec3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

static glm::vec3 refract(glm::vec3& uv, glm::vec3& n, float etai_over_etat) {
	auto cos_theta = fmin(dot(-uv, n), 1.0f);
	glm::vec3 rOutPerp = etai_over_etat * (uv + cos_theta*n);
	glm::vec3 rOutPara = -sqrt(fabs(1.0f - length_squared(rOutPerp))) * n;
	
	return rOutPerp + rOutPara;
}

static glm::vec3 randomInUnitDisk() {
	while (true) {
		auto p = glm::vec3(randomFloat(-1, 1), randomFloat(-1,1), 0);
		if (length_squared(p) >= 1.0f) continue;
		return p;
	}
}