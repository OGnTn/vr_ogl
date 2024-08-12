#include "user/light.h"

Light::Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 lightColor) : shader("../res/shaders/light.vert", "../res/shaders/light.frag"), Node3D(position, rotation, scale, shader, "")
{
    this->meshes = std::vector<Mesh>();
    this->lightColor = lightColor;
    this->shader.Activate();
    glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
}
Light::Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 lightColor, std::string mesh_path) : shader("../res/shaders/light.vert", "../res/shaders/light.frag"), Node3D(position, rotation, scale, shader, mesh_path)
{
    //this->meshes = std::vector<Mesh>();
    this->lightColor = lightColor;
    this->shader.Activate();
    glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
}
