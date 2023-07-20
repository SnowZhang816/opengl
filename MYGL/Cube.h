#pragma once

#include "Render.h"

class Cube : public Render
{
public:
    Cube(float x, float y, float z);
    ~Cube();

    void draw(Camera *ca, Light *light);
private:
    Texture *tex1;
    Texture *tex2;
};

