#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"
#include "building.h"


class Grid {
public:
    Grid(int rows, int cols, glm::vec3 startPos, glm::vec3 buildingSize);  // Constructor
    ~Grid();  // Destructor

    void init();  // Initialize the grid of buildings
    void render();  // Render all buildings

    void setCamera(Camera* camera);  // Set camera for the buildings
    void setShader(wolf::Program* shader);  // Set shader for the buildings
    glm::vec3 getSize() const;

private:
    int m_rows, m_cols;  // Number of rows and columns
    glm::vec3 m_startPos;  // Starting position for grid generation
    glm::vec3 m_buildingSize;  // Size of each building

    std::vector<Building*> m_buildings;  // Vector of Building pointers
};
