#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"
#include "building.h"
#include "sun.h"


class Grid {
public:
    Grid(glm::vec3 startPos, glm::vec3 endPos);  // Constructor
    ~Grid();  // Destructor

    void init();  // Initialize the grid of buildings
    void render();  // Render all buildings

    void setCameraShaderSun(Camera* camera, wolf::Program* shader, wolf::Program* roofShader, Sun* sun);

    std::vector<Building*> getBuildings();

private:
    glm::vec3 m_startPos;  // Starting position for grid generation
    glm::vec3 m_endPos;     //Where the grid should end generating
    
    std::vector<Building*> m_buildings;  // Vector of Building pointers

    void generateGrid();

    float gap;      // Gap between buildings

    Camera* camera;
    wolf::Program* shaderRoof;
    wolf::Program* shaderWalls;

};
