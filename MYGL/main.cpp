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
#include "Quad.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double x, double y);
void mouse_button(GLFWwindow *window, int button, int action, int mods);
void mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);

bool leftEnter = false;
bool rightEnter = false;

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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button);
    glfwSetScrollCallback(window, mouse_scroll);

    int maxAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttribs);
    std::cout << "Max vertex attributes supported : " << maxAttribs << endl;
 
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);

    float degree = 45;
    float radio = 3;
    ca.setPosition(glm::vec3(sin(glm::radians(degree)) * radio, 3.0f, cos(glm::radians(degree)) * radio));
    ca.setLookAt(glm::vec3(0));
    ca.setUp(glm::vec3(0.0f, 1.0f, 0.0f));

    Grid grid = Grid();
    Quad q = Quad(100,100);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        q.draw(&ca);
        grid.draw(&ca);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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
