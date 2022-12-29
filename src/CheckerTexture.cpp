#include "CheckerTexture.h"

CheckerTexture::CheckerTexture()
: even(nullptr), odd(nullptr) {}

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd)
: even(_even), odd(_odd) {}

CheckerTexture::CheckerTexture(glm::vec3 c1, glm::vec3 c2)
: even(std::make_shared<SolidColor>(c1)), odd(std::make_shared<SolidColor>(c2)) {}

glm::vec3 CheckerTexture::value(float u, float v, glm::vec3& p)
{
    auto sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
    if (sines < 0)
        return odd->value(u, v, p);
    else
        return even->value(u, v, p);
}
