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

    // Calculate the angle for horizontal movement (east to west, around the Y-axis)
    float angleZ = elapsedTime * 0.1f;  // Horizontal movement speed (east-west)

    // Calculate the sun's position
    float altitude = glm::radians(45.0f);  // 45 degrees altitude

    // Update the light direction based on the angleZ for horizontal movement and fixed altitude
    lightDirection.x = radius * cos(altitude) * cos(angleZ);  // X-direction
    lightDirection.y = radius * sin(altitude);  // Y-direction
    lightDirection.z = radius * cos(altitude) * sin(angleZ);  // Z-direction

    // Normalize the light direction to ensure it's a unit vector
    lightDirection = glm::normalize(lightDirection);

    // Optionally adjust ambient light intensity based on time of day
    ambientLight = glm::vec3(0.2f) + glm::vec3(0.3f) * glm::clamp(sin(angleZ), 0.0f, 1.0f);
}
