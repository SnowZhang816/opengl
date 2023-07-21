#include "Node.h"

Node::Node() : position(glm::vec3(0)), scale(glm::vec3(1))
{

}

Node::~Node()
{
}

void Node::setPosition(glm::vec3 pos)
{
    this->position = pos;
}

glm::vec3 Node::getPosition() {
    return this->position;
}

void Node::setScale(glm::vec3 s)
{
    this->scale = s;
}

glm::vec3 Node::getScale() {
    return this->scale;
}
