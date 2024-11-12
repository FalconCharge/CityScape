#pragma once
#include "../wolf/wolf.h"
#include <iostream>

class Camera
{
public:
    Camera(wolf::App* pApp);
    virtual ~Camera();

    void update(float dt);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjMatrix(int width, int height);
    glm::vec3 getViewPosition();

private:

    float m_rotX                = 0.0f;
    float m_rotY                = 0.0f;
    float m_distance            = 100.0f;
    glm::vec3 m_offset          = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 m_position        = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 m_target          = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 m_focusMin        = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 m_focusMax        = glm::vec3(0.0f,0.0f,0.0f);
    float m_fov                 = glm::radians(45.0f);
    float m_near                = 0.1f;
    float m_far                 = 1000.0f;
    wolf::App* m_pApp           = nullptr;
};
