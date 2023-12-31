#pragma once

#include "Render.h"
#include <vector>

class Cube : public Render
{
public:
    Cube(float x, float y, float z);
    ~Cube();

    void draw(Camera *ca, const std::vector<Light> &lights, Light &spotlight);
    void drawSimple(Camera *ca);

    void setTexture(Texture *tex);
private:
    Texture *tex1;
    Texture *tex2;
    Texture *tex3;
};

