#pragma once 
#include "../wolf/wolf.h"
#include <glm/gtx/rotate_vector.hpp>

class Sun {
public:
    // Constructor with default values
    Sun();

    // Getter and setter for light direction
    glm::vec3 getLightDirection() const;
    void setLightDirection(const glm::vec3& direction);

    // Getter and setter for light color
    glm::vec3 getLightColor() const;
    void setLightColor(const glm::vec3& color);

    // Getter and setter for ambient light
    glm::vec3 getAmbientLight() const;
    void setAmbientLight(const glm::vec3& ambient);

    // Update function for a day/night cycle
    void update(float dt);
    glm::vec3 getPosition() const;

private:
    glm::vec3 lightDirection;  // Direction of the light (normalized)
    glm::vec3 lightColor;      // Color of the light
    glm::vec3 ambientLight;    // Ambient light color

    float elapsedTime;         // Elapsed time to track the sun's movement
    const float radius = 50.0f;// Radius of the sun's orbit around the center
};
