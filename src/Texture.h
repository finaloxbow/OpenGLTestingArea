#pragma once

#include <glm/glm.hpp>

class Texture {
public:
	virtual glm::vec3 value(float u, float v, glm::vec3& p) = 0;
};

class SolidColor : public Texture {
public:
	SolidColor();
	SolidColor(glm::vec3 c);
	SolidColor(float red, float green, float blue);

	virtual glm::vec3 value(float u, float v, glm::vec3& p) override;

private:
	glm::vec3 colorValue;
};