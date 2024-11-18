#pragma once
#include "../wolf/wolf.h"
#include <iostream>

class Camera
{
public:
    Camera(wolf::App* pApp);
    virtual ~Camera();

    void update(float dt);
    void init();
    void invertCamera();
    
    glm::mat4 getViewMatrix();
    glm::mat4 getProjMatrix(int width, int height);
    glm::vec3 getViewPosition();



private:
    // Private variables for camera properties
    glm::vec3 m_position = glm::vec3(0.0f, 10.0f, 0.0f);  // Camera position
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);     // Front direction vector
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);         // Up direction vector
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);       // Right direction vector
    
    // Camera angles
    float m_yaw = -90.0f;  // Yaw, in degrees, initially pointing to -Z
    float m_pitch = 0.0f;  // Pitch, in degrees
    float m_fov = glm::radians(45.0f);  // Field of view
    float m_near = 0.1f;   // Near clipping plane
    float m_far = 1000.0f; // Far clipping plane
    bool m_inverted = false;

    wolf::App* m_pApp = nullptr;  // Pointer to the application (wolf::App)
    
    // Helper function to update the camera's front, right, and up vectors
    void updateCameraVectors();
    
};
