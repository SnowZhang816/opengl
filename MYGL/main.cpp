//https://code.266.com/unity/udemo

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
#include "Light.h"
#include "Cube.h"
#include "Model.h"
#include <map>
#include "RenderTexture.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double x, double y);
void mouse_button(GLFWwindow *window, int button, int action, int mods);
void mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);

void updateColorDelta(float *total, float *delta);

bool leftEnter = false;
bool rightEnter = false;

Camera ca = Camera(PERSPECTIVE);

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
    // glDepthFunc(GL_ALWAYS);

    ca.setPosition(glm::vec3(0,30.0f,60.0f));
    // ca.setPosition(glm::vec3(sin(glm::radians(degree)) * radio, 3.0f, cos(glm::radians(degree)) * radio));
    ca.setLookAt(glm::vec3(0));
    ca.setUp(glm::vec3(0.0f, 1.0f, 0.0f));

    Grid grid = Grid();

    Quad quad = Quad(200,200);
    quad.setRotation(glm::vec3(90,0,0));

    Cube cube = Cube(10,10,10);
    cube.setPosition(glm::vec3(0, 5.1, 0));

    Light light1 = Light(glm::vec3(1,1,1));
    light1.setPosition(glm::vec3(0,1,10));
    float radio = 10;
    float degree = 0;
    float delta = 0.0003;
    float total = 0;
    // light1.setPosition(glm::vec3(glm::sin(glm::radians(degree)) * radio, 0.0f, glm::cos(glm::radians(degree)) * radio));

    Light light2 = Light(glm::vec3(1,1,1));
    light2.setPosition(glm::vec3(0,10,0));
    Light light3 = Light(glm::vec3(1,1,1));
    light3.setPosition(glm::vec3(0,0,-10));
    Light light4 = Light(glm::vec3(1,1,1));
    light4.setPosition(glm::vec3(-10,0,0));
    std::vector<Light> lights;
    lights.push_back(light1);
    lights.push_back(light2);
    lights.push_back(light3);
    lights.push_back(light4);

    Light spotLight = Light(glm::vec3(1,1,1));
    spotLight.setPosition(glm::vec3(0,0,20));
    spotLight.setDirection(glm::vec3(0,0,-1));
    spotLight.setCutOff(glm::cos(glm::radians(15.0f)));
    spotLight.setOuterCutOff(glm::cos(glm::radians(18.0f)));

    Model model = Model("assets/modle/nanosuit/nanosuit.obj");
    model.setPosition(glm::vec3(10,0,0));

    std::vector<Quad> quads;
    Quad quad1 = Quad(5,5);
    quad1.setPosition(glm::vec3(-5, 2.5, 3));
    quad1.setTexture(new Texture("assets/image/grass.png"));
    quads.push_back(quad1);
    Quad quad2 = Quad(3,3);
    quad2.setPosition(glm::vec3(0, 1.5, 2));
    quad2.setTexture(new Texture("assets/image/grass.png"));
    quads.push_back(quad2);
    Quad quad3 = Quad(16,16);
    quad3.setPosition(glm::vec3(8, 8, 1));
    quad3.setTexture(new Texture("assets/image/grass.png"));
    quads.push_back(quad3);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);

    Quad mirror = Quad(50,50);
    mirror.setShader(new Shader("assets/shader/shader_back.vsh", "assets/shader/shader_back.fsh"));
    mirror.setPosition(glm::vec3(30, 25, -50));

    Quad mirror1 = Quad(50,50);
    mirror1.setPosition(glm::vec3(-30, 25, -50));

    RenderTexture renderTexture = RenderTexture();
    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glBindFramebuffer(GL_FRAMEBUFFER, renderTexture.frameBuffer);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        degree = degree + 0.01;

        // spotLight.setPosition(glm::vec3(glm::sin(glm::radians(degree)) * radio, 0.0f, glm::cos(glm::radians(degree)) * radio));

        updateColorDelta(&total, &delta);

        glm::vec3 lightColor = glm::vec3(1.0f);
        // lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
        // lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
        // lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
        light1.setColor(lightColor);

        // for (size_t i = 0; i < lights.size(); i++)
        // {
        //     Light light = lights.at(i);
        //     light1.draw(&ca);
        // }
        // spotLight.draw(&ca);
        quad.draw(&ca, lights, spotLight);
        // cube.setScale(glm::vec3(2.0f));
        // cube.draw(&ca, lights, spotLight);

        // glEnable(GL_STENCIL_TEST);
        // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        // glStencilFunc(GL_ALWAYS, 1, 0xff);
        // glStencilMask(0xFF); // 启用模板缓冲写入
        // cube.setScale(glm::vec3(1.0f));
        // cube.draw(&ca, lights, spotLight);

        // glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        // glStencilMask(0x00); // 禁止模板缓冲的写入
        // glDisable(GL_DEPTH_TEST);
        // cube.setScale(glm::vec3(1.05));
        // cube.drawSimple(&ca);

        // glStencilMask(0xFF);
        // glEnable(GL_DEPTH_TEST);
        // glDisable(GL_STENCIL_TEST);


        //透明物体
        std::map<float, Quad> tempQuads;
        for (int i = 0; i < quads.size(); i++)
        {
            float dis = glm::length(ca.getPosition() - quads[i].getPosition());
            tempQuads[dis] = quads[i];
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (std::map<float, Quad>::reverse_iterator it = tempQuads.rbegin(); it != tempQuads.rend(); ++it)
        {
            it->second.draw(&ca, lights, spotLight);
        }
        // for (int i = 0; i < quads.size(); i++)
        // {
        //     quads[i].draw(&ca, lights, spotLight);
        // }
        

        // model.setScale(glm::vec3(1.0f));
        // model.draw(&ca, lights, spotLight);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        quad.draw(&ca, lights, spotLight);
        mirror.setTexture(new Texture(renderTexture.texColorBuffer));
        mirror.draw(&ca, lights, spotLight);
        // mirror1.setTexture(new Texture("assets/image/awesomeface.png"));
        // mirror1.draw(&ca, lights, spotLight);

        for (int i = 0; i < quads.size(); i++)
        {
            float dis = glm::length(ca.getPosition() - quads[i].getPosition());
            tempQuads[dis] = quads[i];
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (std::map<float, Quad>::reverse_iterator it = tempQuads.rbegin(); it != tempQuads.rend(); ++it)
        {
            it->second.draw(&ca, lights, spotLight);
        }




        // grid.draw(&ca);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void updateColorDelta(float *total, float *delta)
{
    *total += *delta;
    if (*total >= 1) {
        *total = 1;
        *delta = -*delta;
    } 
    if (*total <= 0) {
        *total = 0;
        *delta = -*delta;
    }
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

    const float cameraSpeed = 1; // adjust accordingly
    const float rotateSpeed = 0.1f; // adjust accordinglydd
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (ca.getCameraProjection() == PERSPECTIVE) {
             ca.focusMove(cameraSpeed);
        } else {
            ca.move(glm::vec3(0, cameraSpeed * 0.1, 0));
        }
       
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if (ca.getCameraProjection() == PERSPECTIVE) {
             ca.focusMove(-cameraSpeed);
        } else {
            ca.move(glm::vec3(0, -cameraSpeed * 0.1, 0));
        }
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if (ca.getCameraProjection() == PERSPECTIVE) {
            ca.rotateYaw(-rotateSpeed);
        } else {
            ca.move(glm::vec3(-cameraSpeed * 0.1, 0, 0));
        }
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if (ca.getCameraProjection() == PERSPECTIVE) {
            ca.rotateYaw(rotateSpeed);
        } else {
            ca.move(glm::vec3(cameraSpeed * 0.1, 0, 0));
        }
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
    float cameraSpeed = 1;
    if (yoffset == 1) {
         ca.focusMove(cameraSpeed);
    } else {
         ca.focusMove(-cameraSpeed);
    }
}
