#include "Cube.h"
#include <cstdio>

Cube::Cube(float x, float y, float z)
{       
    float vertices[] = {
        -x/2.0f, -y/2.0f, -z/2.0f,  0.0f,  0.0f, -1.0f,   1.0, 1.0, 1.0,   0, 0,
         x/2.0f, -y/2.0f, -z/2.0f,  0.0f,  0.0f, -1.0f,   1.0, 1.0, 1.0,   1, 0,
         x/2.0f,  y/2.0f, -z/2.0f,  0.0f,  0.0f, -1.0f,   1.0, 1.0, 1.0,   1, 1,
         x/2.0f,  y/2.0f, -z/2.0f,  0.0f,  0.0f, -1.0f,   1.0, 1.0, 1.0,   1, 1,
        -x/2.0f,  y/2.0f, -z/2.0f,  0.0f,  0.0f, -1.0f,   1.0, 1.0, 1.0,   0, 1,
        -x/2.0f, -y/2.0f, -z/2.0f,  0.0f,  0.0f, -1.0f,   1.0, 1.0, 1.0,   0, 0,

        -x/2.0f, -y/2.0f,  z/2.0f,  0.0f,  0.0f,  1.0f,   1.0, 1.0, 1.0,   0, 0,
         x/2.0f, -y/2.0f,  z/2.0f,  0.0f,  0.0f,  1.0f,   1.0, 1.0, 1.0,   1, 0,
         x/2.0f,  y/2.0f,  z/2.0f,  0.0f,  0.0f,  1.0f,   1.0, 1.0, 1.0,   1, 1,
         x/2.0f,  y/2.0f,  z/2.0f,  0.0f,  0.0f,  1.0f,   1.0, 1.0, 1.0,   1, 1,
        -x/2.0f,  y/2.0f,  z/2.0f,  0.0f,  0.0f,  1.0f,   1.0, 1.0, 1.0,   0, 1,
        -x/2.0f, -y/2.0f,  z/2.0f,  0.0f,  0.0f,  1.0f,   1.0, 1.0, 1.0,   0, 0,

        -x/2.0f,  y/2.0f,  z/2.0f, -1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   1, 1,
        -x/2.0f,  y/2.0f, -z/2.0f, -1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   0, 1,
        -x/2.0f, -y/2.0f, -z/2.0f, -1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   0, 0,
        -x/2.0f, -y/2.0f, -z/2.0f, -1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   0, 0,
        -x/2.0f, -y/2.0f,  z/2.0f, -1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   1, 0,
        -x/2.0f,  y/2.0f,  z/2.0f, -1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   1, 1,

         x/2.0f,  y/2.0f,  z/2.0f,  1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   1, 1,
         x/2.0f,  y/2.0f, -z/2.0f,  1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   0, 1,
         x/2.0f, -y/2.0f, -z/2.0f,  1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   0, 0,
         x/2.0f, -y/2.0f, -z/2.0f,  1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   0, 0,
         x/2.0f, -y/2.0f,  z/2.0f,  1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   1, 0,
         x/2.0f,  y/2.0f,  z/2.0f,  1.0f,  0.0f,  0.0f,   1.0, 1.0, 1.0,   1, 1,

        -x/2.0f, -y/2.0f, -z/2.0f,  0.0f, -1.0f,  0.0f,   1.0, 1.0, 1.0,   0, 1,
         x/2.0f, -y/2.0f, -z/2.0f,  0.0f, -1.0f,  0.0f,   1.0, 1.0, 1.0,   1, 1,
         x/2.0f, -y/2.0f,  z/2.0f,  0.0f, -1.0f,  0.0f,   1.0, 1.0, 1.0,   1, 0,
         x/2.0f, -y/2.0f,  z/2.0f,  0.0f, -1.0f,  0.0f,   1.0, 1.0, 1.0,   1, 0,
        -x/2.0f, -y/2.0f,  z/2.0f,  0.0f, -1.0f,  0.0f,   1.0, 1.0, 1.0,   0, 0,
        -x/2.0f, -y/2.0f, -z/2.0f,  0.0f, -1.0f,  0.0f,   1.0, 1.0, 1.0,   0, 1,

        -x/2.0f,  y/2.0f, -z/2.0f,  0.0f,  1.0f,  0.0f,   1.0, 1.0, 1.0,   0, 1,
         x/2.0f,  y/2.0f, -z/2.0f,  0.0f,  1.0f,  0.0f,   1.0, 1.0, 1.0,   1, 1,
         x/2.0f,  y/2.0f,  z/2.0f,  0.0f,  1.0f,  0.0f,   1.0, 1.0, 1.0,   1, 0,
         x/2.0f,  y/2.0f,  z/2.0f,  0.0f,  1.0f,  0.0f,   1.0, 1.0, 1.0,   1, 0,
        -x/2.0f,  y/2.0f,  z/2.0f,  0.0f,  1.0f,  0.0f,   1.0, 1.0, 1.0,   0, 0,
        -x/2.0f,  y/2.0f, -z/2.0f,  0.0f,  1.0f,  0.0f,   1.0, 1.0, 1.0,   0, 1,
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // normal attribute
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(3);

     // texture
    tex1 = new Texture("assets/image/container2.png", GL_RGBA);
    tex2 = new Texture("assets/image/container2_specular.png", GL_RGBA);
    tex3 = new Texture("assets/image/matrix.jpg", GL_RGB);

    shader = new Shader("assets/shader/shader.vsh", "assets/shader/shader.fsh");
}

Cube::~Cube(){

}

void Cube::draw(Camera *ca, const std::vector<Light> &lights, Light &spotlight)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->position);

    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", ca->getViewMatrix());
    shader->setMat4("projection", ca->getProjectionMatrix());
    shader->setFloat("intensity", 0.2);
    shader->setVec3("viewPos", ca->getPosition());
    // shader->setVec3("material.ambient", glm::vec3(0.0f, 0.1f, 0.06f));
    // shader->setVec3("material.diffuse", glm::vec3(0.0f, 0.50980392f, 0.50980392f));
    // shader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader->setFloat("material.shininess", 10.0f);

    //平行光
    shader->setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader->setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    shader->setVec3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken diffuse light a bit
    shader->setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f)); 

    //点光源
    shader->setInt("pointLightNum", lights.size());
    for (int i = 0; i < lights.size(); i++)
    {
        Light light = lights.at(i);
        char buff[100];
        sprintf_s(buff, "pointLights[%d].position", i);
        shader->setVec3(buff, light.getPosition());
        sprintf_s(buff, "pointLights[%d].ambient", i);
        shader->setVec3(buff, light.getColor() * glm::vec3(0.1));
        sprintf_s(buff, "pointLights[%d].diffuse", i);
        shader->setVec3(buff, light.getColor() * glm::vec3(0.5f)); // darken diffuse light a bit
        sprintf_s(buff, "pointLights[%d].specular", i);
        shader->setVec3(buff, glm::vec3(1.0f, 1.0f, 1.0f)); 
        sprintf_s(buff, "pointLights[%d].constant", i);
        shader->setFloat(buff,  1.0f);
        sprintf_s(buff, "pointLights[%d].linear", i);
        shader->setFloat(buff, 0.014f);
        sprintf_s(buff, "pointLights[%d].quadratic", i);
        shader->setFloat(buff, 0.0007f);
    }

    //聚光灯
    shader->setVec3("spotLight.direction", spotlight.getDirection());
    shader->setVec3("spotLight.position", spotlight.getPosition());
    shader->setVec3("spotLight.ambient", spotlight.getColor() * glm::vec3(0.1));
    shader->setVec3("spotLight.diffuse", spotlight.getColor() * glm::vec3(0.5f)); // darken diffuse light a bit
    shader->setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f)); 
    shader->setFloat("spotLight.cutOff", spotlight.getCutOff()); 
    shader->setFloat("spotLight.outerCutOff", spotlight.getOuterCutOff()); 
    shader->setFloat("spotLight.constant", 1.0f); 
    shader->setFloat("spotLight.linear", 0.014f); 
    shader->setFloat("spotLight.quadratic", 0.0007f); 
    
    shader->setInt("material.diffuse", 0);
    shader->setInt("material.specular", 1);
    shader->setInt("texture1", 2);
    tex1->use(GL_TEXTURE0);
    tex2->use(GL_TEXTURE1);
    tex3->use(GL_TEXTURE2);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}