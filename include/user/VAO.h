#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VBO.h"

class VAO
{
    public:
        GLuint ID;
        VAO();
        void LinkVBO(VBO& VBO, GLuint layout);
        void Bind();
        void Unbind();
        void Delete();
};

#endif