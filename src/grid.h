#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"
#include "building.h"


class Grid {
public:
    Grid(glm::vec3 startPos, glm::vec3 endPos);  // Constructor
    ~Grid();  // Destructor

    void init();  // Initialize the grid of buildings
    void render();  // Render all buildings

    void setCamera(Camera* camera);  // Set camera for the buildings
    void setShader(wolf::Program* shader, wolf::Program* roofShader);  // Set shader for the buildings
    void printGrid();
    glm::vec3 getGridSize() const;
    std::vector<Building*> getBuildings();

private:
    glm::vec3 m_startPos;  // Starting position for grid generation
    glm::vec3 m_endPos;     //Where the grid should end generating
    
    Building* build;

    std::vector<Building*> m_buildings;  // Vector of Building pointers
    std::vector<std::vector<int>> m_grid;


    std::vector<Building*> prevRowBuildings; // Stores buildings from the previous row
    std::vector<Building*> currentRowBuildings; // Stores buildings from the current row


    void generateGrid();


    float gap;      // Gap between buildings

    Camera* camera;
    wolf::Program* shaderRoof;
    wolf::Program* shaderWalls;

};
