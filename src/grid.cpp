#include "grid.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For srand()
#include <random>

Grid::Grid(int rows, int cols, glm::vec3 startPos)
    : m_rows(rows), m_cols(cols), m_startPos(startPos) {}

Grid::~Grid() {
    // Clean up buildings
    for (auto& building : m_buildings) {
        delete building; 
    }
}

void Grid::init(){
    glEnable(GL_DEPTH_TEST);
    std::srand(std::time(0));

    m_buildings.clear();

    fakeGrid = new FakeGrid(m_rows, m_cols);

    for(int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_cols; ++j){

            // Generate random dimensions for the building
            int randomHeight = std::rand() % 5 + 1; // Height: 1 to 5
            int randomWidth = std::rand() % 2 + 1;  // Width: 1 to 2
            int randomDepth = std::rand() % 2 + 1;  // Depth: 1 to 2

            glm::vec3 randomBuildingSize = glm::vec3(randomWidth, randomHeight, randomDepth);
            
            glm::vec3 position = glm::vec3(i, 0.0f, j);

            Building* building = new Building(position, randomBuildingSize);
            building->init();
            m_buildings.push_back(building);

            if(fakeGrid->placeBuilding(i, j, building)){
                m_buildings.push_back(building);
            }
        }
    }
    fakeGrid->printGrid();

}



void Grid::render() {
    // Render all buildings in the grid
    for (auto& building : m_buildings) {
        building->render(); 
    }
}
void Grid::setCamera(Camera* camera) {
    //Set the camera
    for (auto& building : m_buildings) {
        building->setCamera(camera); 
    }
}
void Grid::setShader(wolf::Program* shader) {
    // Set shaders
    for (auto& building : m_buildings) {
        building->setShader(shader); 
    }
}
void Grid::printGrid() {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            std::cout << "[" << m_grid[i][j] << "] ";
        }
        std::cout << std::endl;  // New line after each row
    }
    std::cout << std::endl;
}
// Function to check surrounding squares and return true if any cell has a value other than 0
bool Grid::checkSurroundingSquares(int i, int j, int m_rows, int m_cols, const std::vector<std::vector<int>>& m_grid) {
    // List of directions: (dx, dy)
    std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},  // Top-left, Top, Top-right
        {0, -1}, {0, 1},              // Left, Right
        {1, -1}, {1, 0}, {1, 1}       // Bottom-left, Bottom, Bottom-right
    };

    // Loop through all surrounding squares
    for (const auto& dir : directions) {
        int new_i = i + dir.first;
        int new_j = j + dir.second;

        // Check if the new indices are within the bounds of the grid
        if (new_i >= 0 && new_i < m_rows && new_j >= 0 && new_j < m_cols) {
            if (m_grid[new_i][new_j] != 0) {
                // If the cell has any value other than 0, return true
                return true;
            }
        }
    }

    // Return false if no surrounding cells had a value other than 0
    return false;
}

