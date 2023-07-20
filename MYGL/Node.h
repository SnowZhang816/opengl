#pragma once

#include <glm/glm.hpp>

class Node
{
public:
    Node();
    ~Node();

    void setPosition(glm::vec3 pos);

    glm::vec3 getPosition();
protected:
    glm::vec3 position;
};

