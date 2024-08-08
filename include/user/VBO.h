#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Color;
    glm::vec2 TexCoords;
};

class VBO
{
    public:
        GLuint ID;
        VBO(std::vector<Vertex>& vertices);
        void Bind();
        void Unbind();
        void Delete();
};

#endif