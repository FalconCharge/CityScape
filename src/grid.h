#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"
#include "building.h"
#include "fakeGrid.h"


class Grid {
public:
    Grid(int rows, int cols, glm::vec3 startPos);  // Constructor
    ~Grid();  // Destructor

    void init();  // Initialize the grid of buildings
    void render();  // Render all buildings

    void setCamera(Camera* camera);  // Set camera for the buildings
    void setShader(wolf::Program* shader);  // Set shader for the buildings
    glm::vec3 getSize() const;
    void printGrid();

private:
    int m_rows, m_cols;  // Number of rows and columns
    glm::vec3 m_startPos;  // Starting position for grid generation
    
    Building* build;

    std::vector<Building*> m_buildings;  // Vector of Building pointers
    std::vector<std::vector<int>> m_grid;

    FakeGrid* fakeGrid;

    bool checkSurroundingSquares(int i, int j, int m_rows, int m_cols, const std::vector<std::vector<int>>& m_grid);
    void setupBuildings();

};
