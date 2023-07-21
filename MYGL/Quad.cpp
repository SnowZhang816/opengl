#include "Quad.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Quad::Quad()
{
}

Quad::Quad(float width, float height)
{
    float vertices[] = {
        -width / 2, height / 2, 0.0f,
        width / 2, height / 2, 0.0f,
        width / 2, -height / 2, 0.0f,
        -width / 2, -height / 2, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    float colours[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
    };

    float texCoords[] = {
        0, 1,
        1, 1,
        1, 0,
        0, 0,
    };
    float normal[] = {
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
    };

    unsigned int vbo, ebo, cbo, tbo, nbo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenBuffers(1, &cbo);
    glGenBuffers(1, &tbo);
    glGenBuffers(1, &nbo);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normal), normal, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // texture
    tex1 = new Texture("assets/image/container2.png", GL_RGBA);
    tex2 = new Texture("assets/image/container.jpg", GL_RGB);
    tex3 = new Texture("assets/image/awesomeface.png", GL_RGBA);

    shader = new Shader("assets/shader/shader.vsh", "assets/shader/shader.fsh");
}

Quad::~Quad()
{
}

void Quad::draw(Camera *ca, const std::vector<Light> &lights)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->position);

    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", ca->getViewMatrix());
    shader->setMat4("projection", ca->getProjectionMatrix());
    shader->setFloat("intensity", 0.2);
    shader->setVec3("viewPos", ca->getPosition());
    // shader->setVec3("material.ambient", glm::vec3(0.19125f, 0.0735f, 0.0225f));
    // shader->setVec3("material.diffuse", glm::vec3(0.7038f, 0.27048f, 0.0828f));
    // shader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader->setFloat("material.shininess", 64.0f);
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
        shader->setVec3(buff, light.getColor() * glm::vec3(0.3));
        sprintf_s(buff, "pointLights[%d].diffuse", i);
        shader->setVec3(buff, light.getColor() * glm::vec3(0.5f)); // darken diffuse light a bit
        sprintf_s(buff, "pointLights[%d].specular", i);
        shader->setVec3(buff, glm::vec3(1.0f, 1.0f, 1.0f)); 
        sprintf_s(buff, "pointLights[%d].constant", i);
        shader->setFloat(buff, 1.0f);
        sprintf_s(buff, "pointLights[%d].linear", i);
        shader->setFloat(buff, 0.014f);
        sprintf_s(buff, "pointLights[%d].quadratic", i);
        shader->setFloat(buff, 0.0007f);
    }

    shader->setInt("material.diffuse", 0);
    shader->setInt("material.specular", 1);
    shader->setInt("texture1", 2);
    tex1->use(GL_TEXTURE0);
    tex2->use(GL_TEXTURE1);
    tex3->use(GL_TEXTURE2);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
