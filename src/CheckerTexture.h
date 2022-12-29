#pragma once

#include "Texture.h"
#include <memory>
#include <glm/glm.hpp>

class CheckerTexture : public Texture {
public:
	CheckerTexture();
	CheckerTexture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd);

	CheckerTexture(glm::vec3 c1, glm::vec3 c2);

	virtual glm::vec3 value(float u, float v, glm::vec3& p) override;

private:
	std::shared_ptr<Texture> odd;
	std::shared_ptr<Texture> even;
};