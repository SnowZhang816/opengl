#include "Light.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Light::Light(glm::vec3 c) : color(c)
{
    float vertices[] = {
        -0.1, 0.1, 0,
        0.1, 0.1, 0,
        0.1, -0.1, 0,
        -0.1, -0.1, 0,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
    };
    
    unsigned int vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    shader = new Shader("assets/shader/shader1.vsh", "assets/shader/shader1.fsh");
}

Light::~Light()
{
}


 void Light::draw(Camera *ca){
    shader->use();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->position);
    shader->setMat4("model", model);
    shader->setMat4("view", ca->getViewMatrix());
    shader->setMat4("projection", ca->getProjectionMatrix());
    shader->setVec3("lightColor", color);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 }

 void Light::setColor(glm::vec3 c)
 {
    this->color = c;
 }

  glm::vec3 Light::getColor()
  {
    return this->color;
  }