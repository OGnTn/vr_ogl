#include "user/light.h"

Light::Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 lightColor) : shader("../res/shaders/light.vert", "../res/shaders/light.frag"), Node3D(position, rotation, scale, shader)
{
    this->lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
