#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "user/light.h"

class PointLight : public Light
{
public:
    PointLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 lightColor, float constant, float linear, float quadratic);
    PointLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 lightColor, float constant, float linear, float quadratic, std::string mesh_path);
    float constant;
    float linear;
    float quadratic;
};
#endif