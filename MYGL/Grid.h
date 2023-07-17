#pragma once

#include "Shader.h";

class Grid
{
public:
    Grid();
    ~Grid();

    void setTranslate(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
    void draw();

    unsigned int ID;
    Shader *shader;
};

