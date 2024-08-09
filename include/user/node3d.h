#ifndef NODE3D_H
#define NODE3D_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "user/node.h"
#include "user/mesh.h"
#include "user/shader.h"
#include "user/camera.h"

struct vector3
{
    float x;
    float y;
    float z;
};

class Node3D : public Node
{
    public:
        Node3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Shader& shader);
        void assign_meshes(std::vector<Mesh> meshes);
        void draw(Camera& camera, glm::vec4 lightColor, glm::vec3 lightPos);
        void set_position(glm::vec3 position);
        void set_rotation(glm::vec3 rotation);
        void set_scale(glm::vec3 scale);
        glm::mat4 model;

    private:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        std::vector<Mesh> meshes;
        Shader& shader;
        void update_model();
};

#endif