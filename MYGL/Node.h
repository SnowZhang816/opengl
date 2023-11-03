#pragma once

#include <glm/glm.hpp>

class Node
{
public:
    Node();
    ~Node();

    void setPosition(glm::vec3 pos);
    void setScale(glm::vec3 s);
    void setRotation(glm::vec3 r);

    glm::vec3 getPosition();
    glm::vec3 getScale();
    glm::vec3 getRotation();
protected:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

