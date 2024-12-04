#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"
#include "building.h"


class Grid {
public:
    Grid(int rows, int cols, glm::vec3 startPos);  // Constructor
    ~Grid();  // Destructor

    void init();  // Initialize the grid of buildings
    void render();  // Render all buildings

    void setCamera(Camera* camera);  // Set camera for the buildings
    void setShader(wolf::Program* shader, wolf::Program* roofShader);  // Set shader for the buildings
    glm::vec3 getSize() const;
    void printGrid();
    glm::vec3 getGridSize() const;

private:
    int m_rows, m_cols;  // Number of rows and columns
    glm::vec3 m_startPos;  // Starting position for grid generation
    
    Building* build;

    std::vector<Building*> m_buildings;  // Vector of Building pointers
    std::vector<std::vector<int>> m_grid;


    std::vector<Building*> prevRowBuildings; // Stores buildings from the previous row
    std::vector<Building*> currentRowBuildings; // Stores buildings from the current row


    void generateGrid(glm::vec3 m_startPos);


    float gap;      // Gap between buildings

};
