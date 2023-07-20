#pragma once

#include "Node.h"
#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Light : public Node
{
public: 
    Light(glm::vec3 c = glm::vec3(1.0f));
    ~Light();

    void draw(Camera *ca);

    void setColor(glm::vec3 c);

    glm::vec3 getColor();
private:
    unsigned int VAO;    
    Shader *shader;

    glm::vec3 color;
};

