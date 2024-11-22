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
    generateGrid();


}
void Grid::generateGrid() {
    glEnable(GL_DEPTH_TEST);
    std::srand(std::time(0));


    float gap = 1.0f; // Gap between buildings for spacing
    float cellSize = 1.0f;
    float currentX = 0.0f;
    float currentZ = 0.0f;
    
    for (int x = 1; x < m_rows + 1; ++x) {
        for (int z = 1; z < m_cols + 1; ++z) {
            
            int randomHeight = std::rand() % 10 + 2; // Height: 2 to 11
            int randomWidth = std::rand() % 1 + 1;  // Width: 1
            int randomDepth = std::rand() % 1 + 1;  // Depth: 1

            glm::vec3 size = glm::vec3(randomWidth, randomHeight, randomDepth);

            currentX = x * (size.x + gap); // Add gap after each building in the x-direction
            currentZ = z * (size.z + gap); // Add gap after each building in the z-direction

            glm::vec3 pos = glm::vec3(currentX, 0.0f, currentZ);

            Building* building = new Building();
            building->init();
            building->setPosition(pos);
            building->setScale(size);
            m_buildings.push_back(building);
        }
    }
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

