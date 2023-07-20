#include "Cube.h"

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
    tex1 = new Texture("assets/image/container.jpg", GL_RGB);
    tex2 = new Texture("assets/image/awesomeface.png", GL_RGBA);

    shader = new Shader("assets/shader/shader.vsh", "assets/shader/shader.fsh");
}

Cube::~Cube(){

}

void Cube::draw(Camera *ca, Light *light)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->position);

    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", ca->getViewMatrix());
    shader->setMat4("projection", ca->getProjectionMatrix());
    shader->setFloat("intensity", 0.2);
    shader->setVec3("lightColor", light->getColor());
    shader->setVec3("lightPos", light->getPosition());
    shader->setVec3("viewPos", ca->getPosition());
    shader->setInt("texture2", 1);
    shader->setInt("texture1", 0);
    tex1->use(GL_TEXTURE0);
    tex2->use(GL_TEXTURE1);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}