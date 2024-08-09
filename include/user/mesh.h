#ifndef MESH_H
#define MESH_H

#include <string>

#include "user/VAO.h"
#include "user/EBO.h"
#include "user/texture.h"
#include "user/camera.h"

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO VAO;

    Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures);
    void Draw(Shader &shader, Camera &camera);
};

#endif