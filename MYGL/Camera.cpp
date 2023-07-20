#include "Camera.h"
#include <iostream>

Camera::Camera(CameraProjection type) : projectionType(type), position(glm::vec3(0)), lookAt(glm::vec3(0)), up(glm::vec3(0))
{
    if (projectionType == PERSPECTIVE) {
        perspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    } else {
        ortho(-400, 400.0f, 300.0f, -300.0f, 0.1f, 1000.0f);
    }

    yaw = 0;
    pitch = 0;
    roll = 0;
}

Camera::~Camera()
{
}

void Camera::initFocusCamera(float degree, float radio, glm::vec3 lookAt, glm::vec3 up) {

}

void Camera::ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
    projectionType = ORTHO;
    projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::perspective(float fovy,float aspect,float zNear,float zFar)
{
    projectionType = PERSPECTIVE; 
    projection = glm::perspective(fovy, aspect, zNear, zFar);
}

void Camera::setPosition(glm::vec3 pos)
{
    position = pos;

    float radians = glm::atan(position.x / position.z);
    yaw = glm::degrees(radians);

    float len = glm::length(lookAt - position);
    radians = glm::asin(position.y / len);
    pitch = glm::degrees(radians); 

    std::cout << "setPosition yaw:" << yaw << " pitch:" << pitch << std::endl;

    updateViewMatrix();
}

void Camera::setLookAt(glm::vec3 pos)
{
    lookAt = pos;

    float len = glm::length(lookAt - position);
    float radians = glm::asin(position.y / len);
    pitch = glm::degrees(radians); 

    std::cout << "setLookAt pitch:" << pitch << std::endl;

    updateViewMatrix();
}

void Camera::setUp(glm::vec3 pos)
{
    up = pos;

    updateViewMatrix();
}

void Camera::rotateYaw(float delta)
{
    yaw += delta;

    float radio = glm::length(glm::vec2(lookAt.x - position.x, position.z - lookAt.z));
    position.x = sin(glm::radians(yaw)) * radio;
    position.z = cos(glm::radians(yaw)) * radio;

    updateViewMatrix();
}

void Camera::rotatePitch(float delta)
{
    pitch += delta;

    if (pitch > 89.0f){
        pitch = 89.0f;
    }

    if (pitch < -89.0f){
        pitch = -89.0f;
    }

    float len = glm::length(lookAt - position);

    std::cout << "rotatePitch pitch:" << pitch << "  delta:" << delta << "  len:" << len << std::endl;

    position.y = sin(glm::radians(pitch)) * len;

    position.x = cos(glm::radians(pitch)) * len * sin(glm::radians(yaw));
    position.z = cos(glm::radians(pitch)) * len * cos(glm::radians(yaw));

    updateViewMatrix();
}


void Camera::focusMove(float delta)
{
    position += glm::normalize(lookAt - position) * delta;

    updateViewMatrix();
}

void Camera::move(glm::vec3 delta)
{
    if (projectionType == ORTHO) {
        position += delta;
        lookAt = glm::vec3(position.x, position.y, 0);
    }
    updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
    return view;
}

glm::mat4 Camera::getProjectionMatrix(){
    return projection;
}

void Camera::updateViewMatrix() {
    std::cout << "updateViewMatrix:" << position.x << "," << position.y << ","  << position.z <<  std::endl;
    view = glm::lookAt(position, lookAt, up);
}
