#ifndef EB0_H
#define EB0_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class EBO
{
    public:
        GLuint ID;
        EBO(GLuint* indices, GLsizeiptr size);
        void Bind();
        void Unbind();
        void Delete();
};

#endif