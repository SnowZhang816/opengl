#include "Grid.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Grid::Grid()
{    

    //x
    const int xCount = 11;

    const int zCount = 11;
    const int count = xCount * 12 + zCount * 12;

    float vertices[count] = {};
    for (size_t i = 0; i < xCount; i++)
    {
        //pos
        vertices[i * 12 + 0] = -10.0f;
        vertices[i * 12 + 1] = 0.0f;
        vertices[i * 12 + 2] = -(float)i + (float)xCount / 2.0f;

        //color
        vertices[i * 12 + 3] = 1.0f;
        vertices[i * 12 + 4] = 1.0f;
        vertices[i * 12 + 5] = 1.0f;

        //pos
        vertices[i * 12 + 6] = 10.0f;
        vertices[i * 12 + 7] = 0.0f;
        vertices[i * 12 + 8] = -(float)i + (float)xCount / 2.0f;

        //color
        vertices[i * 12 + 9] = 1.0f;
        vertices[i * 12 + 10] = 1.0f;
        vertices[i * 12 + 11] = 1.0f;
    }

    // float vertices[] = {
    //     //pos
    //     -1.0f,
    //     0.0f,
    //     -0.5,

    //     //color
    //     1.0f,
    //     1.0f,
    //     1.0f,

    //     //pos
    //     1.0f,
    //     0.0f,
    //     -0.5,

    //     //color
    //     1.0f,
    //     1.0f,
    //     1.0f,
    // }; 

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    shader = new Shader("assets/shader/baseshader.vsh", "assets/shader/baseshader.fsh");
}

Grid::~Grid()
{
    delete shader;
}

void Grid::setTranslate(glm::mat4 model, glm::mat4 view, glm::mat4 projection){
    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
}

void Grid::draw()
{
    shader->use();

    glBindVertexArray(ID);
    glLineWidth(2);
    glDrawArrays(GL_LINES, 0, 22);
}
