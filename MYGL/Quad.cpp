#include "Quad.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Quad::Quad()
{
}

Quad::Quad(float width, float height)
{
    // float vertices[] = {
    //     -width / 2, height / 2, 0.0f,
    //     width / 2, height / 2, 0.0f,
    //     width / 2, -height / 2, 0.0f,
    //     -width / 2, -height / 2, 0.0f,
    // };

    // float vertices[] = {
    //     -1.0f, -0.5f, -0.5f,
    //     0.0f, -0.5f, -0.5f,
    //     0.0f, -0.5f, 0.5f,
    //     -1.0f, -0.5f, 0.5f,
    // };

    // float indices[] = {
    //     0, 1, 2,
    //     0, 2, 3,
    // };

    // float colours[] = {
    //     1.0f, 0.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f,
    //     0.0f, 0.0f, 1.0f,
    //     1.0f, 1.0f, 0.0f,
    // };

    // unsigned int vbo, ebo, cbo;
    // glGenBuffers(1, &vbo);
    // glGenBuffers(1, &ebo);
    // glGenBuffers(1, &cbo);
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    // glBindBuffer(GL_ARRAY_BUFFER, cbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // // glBindVertexArray(0);

    // shader = new Shader("assets/shader/baseshader.vsh", "assets/shader/baseshader.fsh");

    float vertices[] = {
        -1.0f, -0.5f, -0.5f,
        0.0f, -0.5f, -0.5f,
        0.0f, -0.5f, 0.5f,
        -1.0f, -0.5f, 0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f};

    float colours[] = {
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,
        0.0f,

        1.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,
        0.0f,
    };

    unsigned int indices[] = {
        // note that we start from 0!
        0,
        1,
        2,
        0,
        2,
        3,
        4,
        5,
        6,
        4,
        6,
        7,

    };

    float texCoords[] = {
        0,
        1,
        1,
        1,
        1,
        0,
        0,
        0,
        0,
        1,
        1,
        1,
        1,
        0,
        0,
        0,
    };

    unsigned int vbo, ebo, cvbo, tvbo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cvbo);
    glGenBuffers(1, &tvbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, cvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, tvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // texture
    tex1 = new Texture("assets/image/container.jpg", GL_RGB);
    tex2 = new Texture("assets/image/awesomeface.png", GL_RGBA);

    shader = new Shader("assets/shader/shader.vsh", "assets/shader/shader.fsh");
}

Quad::~Quad()
{
}

void Quad::draw(Camera *ca)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->position);

    shader->use();
    shader->setMat4("model", glm::mat4(1.0f));
    shader->setMat4("view", ca->getViewMatrix());
    shader->setMat4("projection", ca->getProjectionMatrix());
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
    shader->setFloat("intensity", 0.2);
    tex1->use(GL_TEXTURE0);
    tex2->use(GL_TEXTURE1);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}
