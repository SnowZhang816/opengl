#include "Node.h"

Node::Node() : position(glm::vec3(0))
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
