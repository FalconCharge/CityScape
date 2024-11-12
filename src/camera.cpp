#include "camera.h"

Camera::Camera(wolf::App* pApp): m_pApp(pApp){}

Camera::~Camera()
{
	printf("Destroying Camera\n");
}
void Camera::update(float dt) {
    const float radius = 10.0f;  // Radius of the circle
    float camX = sin(glfwGetTime()) * radius;  // Calculate X position
    float camZ = cos(glfwGetTime()) * radius;  // Calculate Z position

    m_position = glm::vec3(camX, 0.0f, camZ);  // Update the camera position
}
glm::mat4 Camera::getViewMatrix(){      
    return glm::lookAt(getViewPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
glm::mat4 Camera::getProjMatrix(int width, int height)
{
	return glm::perspective(m_fov, (float)width / (float)height, m_near, m_far);
}
glm::vec3 Camera::getViewPosition(){
    std::cout << "Calling matrix " 
          << "m_position: (" 
          << m_position.x << ", " 
          << m_position.y << ", " 
          << m_position.z << ")" 
          << std::endl;
    return m_position;
}
