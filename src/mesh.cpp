#include "user/mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    std::cout << textures.size() << std::endl;

    VAO.Bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, Color));
    VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw(Shader &shader)
{
    shader.Activate();
    VAO.Bind();

    int numDiffuse = 0;
    int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string number;
        std::string type = textures[i].type;

        if (type == "diffuse")
            number = std::to_string(numDiffuse++);
        else if (type == "specular")
            number = std::to_string(numSpecular++);

        textures[i].texUnit(shader, (type + number).c_str(), i);
        // std::cout << "Texture type: " << type << " number: " << number << std::endl;
        textures[i].Bind();
    }
    // glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    // camera.Matrix(shader, "camMatrix");
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}