#include "grid.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For srand()
#include <random>

Grid::Grid(int rows, int cols, glm::vec3 startPos, glm::vec3 buildingSize)
    : m_rows(rows), m_cols(cols), m_startPos(startPos), m_buildingSize(buildingSize) {}

Grid::~Grid() {
    // Clean up buildings
    for (auto building : m_buildings) {
        delete building; 
    }
}


void Grid::init() {
    glEnable(GL_DEPTH_TEST);    //Had to turn this on somereason

    // Seed the random number generator once, ideally in the constructor or init function
    std::srand(std::time(0));

    float gap = 1.0f;           //Gap in the grid
    float baseCellSize = 2.0f;  // Minimum width/depth of a building

    // Loop to generate buildings in a grid pattern
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {

            float width = (std::rand() % 200 + 1)/100;  // Width between 1 and 3 cells
            int depth = (std::rand() % 200 + 1)/100;  // Depth between 1 and 3 cells
            int height = std::rand() % 5 + 1; // Height between 1 and 5 units

            glm::vec3 pos = m_startPos + glm::vec3(i * gap, 0.0f, j * gap);

            glm::vec3 randomBuildingSize = glm::vec3(width, height, depth);

            Building* building = new Building(pos, randomBuildingSize);
            building->init();
            
            m_buildings.push_back(building);
        }
    }
}



void Grid::render() {
    // Render all buildings in the grid
    for (auto building : m_buildings) {
        building->render(); 
    }
}
void Grid::setCamera(Camera* camera) {
    //Set the camera
    for (auto building : m_buildings) {
        building->setCamera(camera); 
    }
}
void Grid::setShader(wolf::Program* shader) {
    // Set shaders
    for (auto building : m_buildings) {
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

