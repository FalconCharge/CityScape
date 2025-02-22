#include "grid.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For srand()
#include <random>

Grid::Grid(glm::vec3 startPos, glm::vec3 endPos)
    : m_endPos(endPos), m_startPos(startPos) {}

Grid::~Grid() {
    // Clean up buildings
    for (auto& building : m_buildings) {
        delete building; 
    }
}

void Grid::init(){
    generateGrid();
}

void Grid::generateGrid() {
    float currentX = m_startPos.x;
    float currentZ = m_startPos.z;

    float gap = 3.0f;

    while (currentZ <= m_endPos.z) { // Loop through rows (Z-axis)
        currentX = m_startPos.x;    // Reset X for each row
        while (currentX <= m_endPos.x) { // Loop through columns (X-axis)
            // Randomize building dimensions
            int height = std::rand() % 10 + 5; // Height:
            int width = std::rand() % 2 + 1;   // Width: 
            int depth = std::rand() % 2 + 1;   // Depth:

            glm::vec3 size(width, height, depth);

            // Ensure the building fits within the grid
            if (currentX + width > m_endPos.x || currentZ + depth > m_endPos.z) {
                break; // Move to the next row or end if no more space
            }

            glm::vec3 position(currentX, 0.0f, currentZ);

            // Add the building to the grid 
            Building* building = new Building();
            building->init(shaderWalls, shaderRoof, camera);
            building->setTransform(position, size);
            m_buildings.push_back(building);
            
            // Increment X position
            currentX += gap;
        }
        // Increment Z position by row depth + gap
        currentZ += gap; // Adjust row gap as needed
    }
}

void Grid::render() {
    // Render all buildings in the grid
    for (auto& building : m_buildings) {
        building->render(); 
    }
}
void Grid::setCameraShaderSun(Camera* camera, wolf::Program* shader, wolf::Program* roofShader, Sun* sun){
    for (auto& building : m_buildings) {
        building->setShader(shader, roofShader); 
        building->setSun(sun);
        building->setCamera(camera);
    }
}

std::vector<Building*> Grid::getBuildings(){
    return m_buildings;
}
