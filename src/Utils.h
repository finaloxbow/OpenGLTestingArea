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