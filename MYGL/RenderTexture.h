#pragma once

#include <glm/glm.hpp>

class RenderTexture
{
public:
    RenderTexture();
    ~RenderTexture();

    unsigned int frameBuffer;
    unsigned int texColorBuffer;
};

