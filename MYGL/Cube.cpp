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
    tex1 = new Texture("assets/image/container2.png", GL_RGBA);
    tex2 = new Texture("assets/image/container2_specular.png", GL_RGBA);
    tex3 = new Texture("assets/image/matrix.jpg", GL_RGB);

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
    shader->setVec3("viewPos", ca->getPosition());
    // shader->setVec3("material.ambient", glm::vec3(0.0f, 0.1f, 0.06f));
    // shader->setVec3("material.diffuse", glm::vec3(0.0f, 0.50980392f, 0.50980392f));
    // shader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader->setFloat("material.shininess", 10.0f);
    shader->setVec3("light.position", light->getPosition());
    shader->setVec3("light.ambient", light->getColor() * glm::vec3(0.3));
    shader->setVec3("light.diffuse", light->getColor() * glm::vec3(0.5f)); // darken diffuse light a bit
    shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f)); 
    shader->setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f)); 
    shader->setFloat("light.constant",  1.0f);
    shader->setFloat("light.linear", 0.014f);
    shader->setFloat("light.quadratic", 0.0007f);


    shader->setInt("material.diffuse", 0);
    shader->setInt("material.specular", 1);
    shader->setInt("texture1", 2);
    tex1->use(GL_TEXTURE0);
    tex2->use(GL_TEXTURE1);
    tex3->use(GL_TEXTURE2);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}