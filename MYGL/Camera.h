#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @en The projection type enumeration of the camera.
 * @zh 相机的投影类型枚举。
 */
enum CameraProjection
{
    /**
     * @en Orthogonal projection type
     * @zh 正交投影类型
     */
    ORTHO,
    /**
     * @en Perspective projection type
     * @zh 透视投影类型
     */
    PERSPECTIVE,
};

class Camera
{
public:
    Camera(CameraProjection type = PERSPECTIVE);
    ~Camera();

    void initFocusCamera(float degree, float radio, glm::vec3 lookAt, glm::vec3 up);

    void ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    void perspective(float fovy,float aspect,float zNear,float zFar);

    void setPosition(glm::vec3 pos);
    void setLookAt(glm::vec3 pos);
    void setUp(glm::vec3 pos);

    glm::vec3 getPosition() {return position;}
    glm::vec3 getLookAt() {return lookAt;}
    glm::vec3 getUp() {return up;}

    CameraProjection getCameraProjection() {return projectionType;}

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void rotateYaw(float degree);
    void rotatePitch(float degree);

    void focusMove(float delta);

protected:
    void updateViewMatrix();

private:
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 up;

    CameraProjection projectionType;

    //投影矩阵
    glm::mat4 projection;
    //视图矩阵
    glm::mat4 view;


    //focus相机参数
    float yaw;
    float pitch;
    float roll;
};
