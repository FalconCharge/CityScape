#include "camera.h"

Camera::Camera(wolf::App* pApp): m_pApp(pApp){}
Camera::~Camera()
{
	printf("Destroying Camera\n");
}
void Camera::init(){
    m_pApp->hideCursor();
    printf("Camera init\n");
}

void Camera::update(float dt) {
    glm::vec2 screenCenter(m_pApp->getScreenSize().x / 2.0f, m_pApp->getScreenSize().y / 2.0f);
    glm::vec2 mousePos = m_pApp->getMousePos();  // Get mouse position (x, y) in window space

    float offsetX = (mousePos.x - screenCenter.x);
    float offsetY = (screenCenter.y - mousePos.y);  // Reverse Y axis

    // Sensitivity settings for camera movement
    const float sensitivity = 0.15f;
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    // Update yaw and pitch based on mouse movement
    m_yaw += offsetX;
    m_pitch += offsetY;

    //Limits from player looking to high
    m_pitch = glm::clamp(m_pitch, -89.0f, 80.0f);

    // Update the front vector based on yaw and pitch
    updateCameraVectors();

    m_pApp->setMousePos(screenCenter.x, screenCenter.y);

    const float cameraSpeed = 2.0f * dt; // Adjust speed based on frame time (dt)
    if (m_pApp->isKeyDown(GLFW_KEY_W)) {
        m_position += m_front * cameraSpeed;
    }
    if (m_pApp->isKeyDown(GLFW_KEY_S)) {
        m_position -= m_front * cameraSpeed;
    }
    if (m_pApp->isKeyDown(GLFW_KEY_A)) {
        m_position -= m_right * cameraSpeed;
    }
    if (m_pApp->isKeyDown(GLFW_KEY_D)) {
        m_position += m_right * cameraSpeed;
    }
    if (m_pApp->isKeyDown(GLFW_KEY_Q)) {
        m_position -= m_up * (cameraSpeed);
    }
    if (m_pApp->isKeyDown(GLFW_KEY_E)) {
        m_position += m_up * (cameraSpeed);
    }

}
void Camera::updateCameraVectors() {
    // Calculate the new front vector based on yaw and pitch
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    // Also re-calculate the right and up vectors
    m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));  // Cross product with up vector
    m_up = glm::normalize(glm::cross(m_right, m_front));  // Recalculate the up vector
}
glm::mat4 Camera::getViewMatrix(){      
    return glm::lookAt(m_position, m_position + m_front, m_up);
}
glm::mat4 Camera::getProjMatrix(int width, int height)
{
	return glm::perspective(m_fov, (float)width / (float)height, m_near, m_far);
}
glm::vec3 Camera::getViewPosition(){
    return m_position;
}
