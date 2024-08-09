#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb/stb_image.h"
#include "shader.h"

class Texture
{
public:
    GLuint ID;
    const char *type;
    GLuint unit;

    Texture(const char *image, const char *texType, GLuint slot, GLenum format, GLenum pixelType);
    Texture(unsigned char *data, int width, int height, int nrColCh, const char *texType, GLuint slot, GLenum format, GLenum pixelType);
    Texture();

    void texUnit(Shader &shader, const char *uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};

#endif