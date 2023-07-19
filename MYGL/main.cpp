#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include "Shader.h"
#include "std_image.h"
#include "Texture.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Grid.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double x, double y);
void mouse_button(GLFWwindow *window, int button, int action, int mods);
void mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);


float degree = 45;
float radio = 3;

bool leftEnter = false;
bool rightEnter = false;

glm::vec3 cameraPos = glm::vec3(sin(glm::radians(degree)) * radio, 3.0f, cos(glm::radians(degree)) * radio);

float radians = glm::atan(cameraPos.x / cameraPos.z);
float degree1 = glm::degrees(radians);

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));

glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
// float radio = glm::length(cameraTarget - cameraPos);
Camera ca = Camera();

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

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button);
    glfwSetScrollCallback(window, mouse_scroll);
    // glfwSetCursorEnterCallback()

    int maxAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttribs);
    std::cout << "Max vertex attributes supported : " << maxAttribs << endl;
    Shader *shader = new Shader("assets/shader/shader.vsh", "assets/shader/shader.fsh");
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
    Grid grid = Grid();

    // 第一个三角形
    float vertices1[] = {
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, -0.0f, 0.0f};

    // 第二个三角形
    float vertices2[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f};

    unsigned int VAO[2], VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    // 创建并绑定VBO（Vertex Buffer Object），将顶点数据复制到缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    // 创建并绑定VBO（Vertex Buffer Object），将顶点数据复制到缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 创建并编译第一个顶点着色器
    Shader s1 = Shader("assets/shader/shader1.vsh", "assets/shader/shader1.fsh");

    // 创建并编译第二个顶点着色器
    Shader s2 = Shader("assets/shader/shader2.vsh", "assets/shader/shader2.fsh");

    ca.setPosition(glm::vec3(sin(glm::radians(degree)) * radio, 0.0f, cos(glm::radians(degree)) * radio));
    ca.setLookAt(glm::vec3(0));
    ca.setUp(cameraUp);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        // model = glm::rotate(model, 100.f * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f)) * model;
        glm::mat4 view = ca.getViewMatrix();
        glm::mat4 projection = ca.getProjectionMatrix();

        grid.setTranslate(model, view, projection);
        grid.draw();

        shader->use();
        shader->setMat4("model", model);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        shader->setInt("texture1", 0);
        shader->setInt("texture2", 1);
        shader->setFloat("intensity", intensity);
        tex1->use(GL_TEXTURE0);
        tex2->use(GL_TEXTURE1);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(float), GL_UNSIGNED_INT, 0);

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
    {
        glfwSetWindowShouldClose(window, true);
    }

    const float cameraSpeed = 0.01; // adjust accordingly
    const float rotateSpeed = 0.1f; // adjust accordinglydd
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        ca.focusMove(cameraSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        ca.focusMove(-cameraSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        ca.rotateYaw(-rotateSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        ca.rotateYaw(rotateSpeed);
    }
}

double xpos;
double ypos;

void mouse_callback(GLFWwindow *window, double x, double y)
{
    if (leftEnter)
    {
        // std::cout << "leftEnter mouse_callback: " << x << "," << y << endl;
        glm::vec2 start = glm::vec2(xpos, ypos);
        glm::vec2 end = glm::vec2(x, y);
        glm::vec2 line = end - start;
        xpos = x;
        ypos = y;
        if (line.x != 0 || line.y != 0)
        {
            float len = glm::length(line);
            glm::vec2 normal = glm::normalize(line);
            float p = 0;
            float q = 0;
            glm::vec2 referY = glm::vec2(0, 1);
            glm::vec2 referX = glm::vec2(1, 0);
            float delta = 0;
            if (end.x > 400 && end.y < 300)
            { // 第一象限
                p = glm::dot(normal, referY);
                glm::vec2 refer2 = glm::vec2(1, 0);
                q = glm::dot(normal, referX);
                if (p == 0)
                {
                    if (q > 0)
                    {
                        delta = len * 0.5;
                    }
                    else
                    {
                        delta = -len * 0.5;
                    }
                }
                else
                {
                    if (p > 0)
                    {
                        delta = len * 0.5;
                    }
                    else
                    {
                        delta = -len * 0.5;
                    }
                }
            }
            else if (end.x < 400 && end.y < 300)
            { // 第二象限
                p = glm::dot(normal, referY);
                glm::vec2 refer2 = glm::vec2(1, 0);
                q = glm::dot(normal, referX);
                if (p == 0)
                {
                    if (q > 0)
                    {
                        delta = len * 0.5;
                    }
                    else
                    {
                        delta = -len * 0.5;
                    }
                }
                else
                {
                    if (p < 0)
                    {
                        delta = len * 0.5;
                    }
                    else
                    {
                        delta = -len * 0.5;
                    }
                }
            }
            else if (end.x < 400 && end.y > 300)
            { // 第三象限
                p = glm::dot(normal, referY);
                glm::vec2 refer2 = glm::vec2(1, 0);
                q = glm::dot(normal, referX);
                if (p == 0)
                {
                    if (q < 0)
                    {
                        delta = len * 0.5;
                    }
                    else
                    {
                        delta = -len * 0.5;
                    }
                }
                else
                {
                    if (p < 0)
                    {
                        delta = len * 0.5;
                    }
                    else
                    {
                        delta = -len * 0.5;
                    }
                }
            }
            else if (end.x > 400 && end.y > 300)
            { // 第四象限
                p = glm::dot(normal, referY);
                glm::vec2 refer2 = glm::vec2(1, 0);
                q = glm::dot(normal, referX);
                if (p == 0)
                {
                    if (q < 0)
                    {
                        delta = len * 0.5;
                    }
                    else
                    {
                        delta = -len * 0.5;
                    }
                }
                else
                {
                    if (p > 0)
                    {
                        delta = len * 0.5;
                    }
                    else
                    {
                        delta = -len * 0.5;
                    }
                }
            }

            // std::cout << "degree" << degree << "," << p << endl;
            ca.rotateYaw(delta);
        }
    }

    if (rightEnter)
    {
        // std::cout << "leftEnter mouse_callback: " << x << "," << y << endl;
        glm::vec2 start = glm::vec2(xpos, ypos);
        glm::vec2 end = glm::vec2(x, y);
        glm::vec2 line = end - start;
        xpos = x;
        ypos = y;
        if (line.x != 0 || line.y != 0)
        {
            float len = glm::length(line);
            glm::vec2 normal = glm::normalize(line);
            glm::vec2 referY = glm::vec2(0, 1);
            float p = glm::dot(normal, referY);
            float delta = 0;
            if (p > 0) {
                delta = len * 0.5;
            } else {
                delta = -len * 0.5;
            }
            // std::cout << "degree" << degree << "," << p << endl;
            ca.rotatePitch(delta);
        }
    }
}

void mouse_button(GLFWwindow *window, int button, int action, int mods)
{
    std::cout << "mouse_button:" << button << "  action:" << action << "  mods:" << mods << endl;

    if (action == 1 && button == 0)
    {
        leftEnter = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwGetCursorPos(window, &xpos, &ypos);
    }

    if (action == 0 && button == 0)
    {
        leftEnter = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        xpos = 0;
        ypos = 0;
    }

    if (action == 1 && button == 1)
    {
        rightEnter = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwGetCursorPos(window, &xpos, &ypos);
    }

    if (action == 0 && button == 1)
    {
        rightEnter = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        xpos = 0;
        ypos = 0;
    }
}

void mouse_scroll(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "mouse_scroll xoffset" << xoffset << "  yoffset:" << yoffset << endl;
    float cameraSpeed = 0.1;
    if (yoffset == 1) {
         ca.focusMove(cameraSpeed);
    } else {
         ca.focusMove(-cameraSpeed);
    }
}
