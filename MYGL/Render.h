#pragma once

#include "Node.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

class Render : public Node
{
public:
    Render();
    ~Render();

    void draw(Camera *ca);
protected:
    unsigned int VAO;    
    Shader *shader;
};

