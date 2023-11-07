#pragma once

#include "Node.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Render.h"
#include <vector>

class Quad : public Render
{
public:
    Quad();
    Quad(float w, float h);
    ~Quad();

    void setTexture(Texture *tex);

    void draw(Camera *ca, const std::vector<Light> &lights, Light &spotlight);
private:
    unsigned int VAO;

    float width;
    float height;

    Texture *tex1;
    Texture *tex2;
    Texture *tex3;
};

