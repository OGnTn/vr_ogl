#include "user/point_light.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 lightColor, float constant, float linear, float quadratic) : Light(position, rotation, scale, lightColor)
{
    this->lightColor = lightColor;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}
PointLight::PointLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 lightColor, float constant, float linear, float quadratic, std::string mesh_path) : Light(position, rotation, scale, lightColor, mesh_path)
{
    this->lightColor = lightColor;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}