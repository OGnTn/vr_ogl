#ifndef LIGHT_H
#define LIGHT_H

#include "user/node3d.h"

class Light : public Node3D
{
public:
    Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 lightColor);
    Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 lightColor, std::string mesh_path);
    glm::vec4 lightColor;
    Shader shader;
};

#endif