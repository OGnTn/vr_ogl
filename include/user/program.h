#ifndef PROGRAM_H
#define PROGRAM_H
#include "user/mesh.h"
#include "user/model_loader.h"
#include "user/node3d.h"
#include <iostream>
#include <string>
#include <glm/gtx/string_cast.hpp>

class Program
{
public:
    const unsigned int width = 800;
    const unsigned int height = 800;

    Program();
    int run();
};
#endif