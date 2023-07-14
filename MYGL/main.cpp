#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include "Shader.h"
#include "std_image.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "learn", NULL, NULL);
    if (window == NULL)
    {
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int maxAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttribs);
    std::cout << "Max vertex attributes supported : " << maxAttribs << endl;
    Shader *shader = new Shader("assets/shader/shader.vsh", "assets/shader/shader.fsh");
    float vertices[] = {
        -0.5f, 0.0f, -0.5f,  
        0.5f, 0.0f, -0.5f, 
        0.5f, -0.0f, 0.5f,
        -0.5f, 0.0f, 0.5f ,

        -0.5f, 1.f, -0.5f,  
        0.5f, 1.f, -0.5f, 
        0.5f, 1.f, 0.5f,
        -0.5f, 1.f, 0.5f 
    };

    float colours[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
    };

    unsigned int indices[] = {
        // note that we start from 0!
        0,1,2,0,2,3,
        4,5,6,4,6,7,
        5,4,1,4,1,0
        
        // 0,1,2,0,2,3,
        // 0,1,2,0,2,3,
        // 0,1,2,0,2,3,
        
    };

    unsigned int indices1[] = {
        // note that we start from 0!
        1, 0, 2, // first triangle
    };

    float texCoords[] = {
        0,1,1,1,1,0,0,0,
        0,1,1,1,1,0,0,0,
        0,1,1,1,1,0,0,0,
    };

    unsigned int vbo, vao, ebo, cvbo, tvbo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cvbo);
    glGenBuffers(1, &tvbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

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

    // texture
    Texture *tex1 = new Texture("assets/image/container.jpg", GL_RGB);
    Texture *tex2 = new Texture("assets/image/awesomeface.png", GL_RGBA);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::vec4 result = trans * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    printf("%f, %f, %f\n", result.x, result.y, result.z);

    glEnable(GL_DEPTH_TEST);

    float intensity = 0.5;
    auto t_start = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        t_start = t_now;

        // GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
        // glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

        // intensity = intensity + time * 0.1;
        // if (intensity > 1)
        // {
        //     intensity = 0;
        // }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, 100.f * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f)) * model;
        shader->setMat4("model", model);

        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        view = glm::rotate(view, 30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        shader->setMat4("view", view);

        glm::mat4 projection;
        projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
        shader->setMat4("projection", projection);

        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.5f));
        transform = glm::rotate(transform, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

        shader->use();
        shader->setInt("texture1", 0);
        shader->setInt("texture2", 1);
        shader->setFloat("intensity", intensity);
        shader->setMat4("transform", transform);
        tex1->use(GL_TEXTURE0);
        tex2->use(GL_TEXTURE1);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(float), GL_UNSIGNED_INT, 0);

        // transform = glm::mat4(1.0f); // reset it to identity matrix
        // transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
        // float scaleAmount = static_cast<float>(sin(glfwGetTime()));
        // transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        // shader->setMat4("transform", transform);
        // glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    delete shader;
    delete tex1;
    delete tex2;

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

