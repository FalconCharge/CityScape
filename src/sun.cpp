#include "Sun.h"
// Constructor initializes default values for the Sun
Sun::Sun() : elapsedTime(0.0f), lightColor(1.0f, 1.0f, 1.0f), ambientLight(0.1f, 0.1f, 0.1f) {}


// Getter for light direction
glm::vec3 Sun::getLightDirection() const {
    return lightDirection;
}

// Setter for light direction
void Sun::setLightDirection(const glm::vec3& direction) {
    lightDirection = glm::normalize(direction);
}

// Getter for light color
glm::vec3 Sun::getLightColor() const {
    return lightColor;
}

// Setter for light color
void Sun::setLightColor(const glm::vec3& color) {
    lightColor = color;
}

// Getter for ambient light
glm::vec3 Sun::getAmbientLight() const {
    return ambientLight;
}

// Setter for ambient light
void Sun::setAmbientLight(const glm::vec3& ambient) {
    ambientLight = ambient;
}

void Sun::update(float dt) {
    elapsedTime += dt;

    // Calculate the angle of rotation based on time
    float angleX = elapsedTime * 0.1f;  // Rotation speed on the X-axis
    float angleZ = elapsedTime * 0.1f;  // Rotation speed on the Z-axis

    // Update the light direction based on the sun's position
    lightDirection.x = radius * cos(angleX);
    lightDirection.y = radius * sin(angleX);  // Y-axis controls the altitude
    lightDirection.z = radius * cos(angleZ);  // Z-axis controls the horizontal movement

    // Normalize the light direction
    lightDirection = glm::normalize(lightDirection);

    // Optional: Adjust ambient light intensity based on time of day
    ambientLight = glm::vec3(0.2f) + glm::vec3(0.3f) * glm::clamp(sin(angleX), 0.0f, 1.0f);
}