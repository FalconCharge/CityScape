#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"

class Building {
public:
    glm::vec3 position;   // Position of the building (x, y, z)
    glm::vec3 size;       // Dimensions (width, height, depth)
    int textureID;        // Texture ID for the building
    
    Building(glm::vec3 position, glm::vec3 size, int textureID);
    void generateMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, int& indexOffset);
    void render(glm::mat4& view, glm::mat4& projection);
};
