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
    Light(glm::vec3 c = glm::vec3(1.0f), glm::vec3 dir = glm::vec3(0,0,-1));
    ~Light();

    void draw(Camera *ca);

    void setColor(glm::vec3 c);
    glm::vec3 getColor();

    void setDirection(glm::vec3 dir);
    glm::vec3 getDirection();

    void setCutOff(float c);
    float getCutOff();

    void setOuterCutOff(float c);
    float getOuterCutOff();
private:
    unsigned int VAO;    
    Shader *shader;

    glm::vec3 color;
    glm::vec3 direction;

    //聚光灯截止角的余弦值
    float cutOff;
    float outerCutOff;
};

