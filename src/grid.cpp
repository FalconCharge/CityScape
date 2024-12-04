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
    generateGrid(m_startPos);
}
void Grid::generateGrid(glm::vec3 m_startPos) {

    std::srand(std::time(0));

    float gap = 1.0f; // Gap between buildings for spacing
    std::vector<Building*> prevRowBuildings; // Stores buildings from the previous row
    std::vector<Building*> currentRowBuildings; // Stores buildings from the current row

    float maxRowLength = m_startPos.x + m_rows + (m_rows * gap);
    float currentZ = m_startPos.z;

    for (int x = 0; x < m_rows; ++x) {
        float currentX = m_startPos.x; // Reset X position for the new row

        for (int z = 0; z < m_cols; ++z) {
            // Randomize building dimensions
            int randomHeight = std::rand() % 10 + 2; // Height: 2 to 11
            int randomWidth = std::rand() % 2 + 1;   // Width: 1 to 3
            int randomDepth = std::rand() % 2 + 1;   // Depth: 1 to 3

            glm::vec3 size = glm::vec3(randomWidth, randomHeight, randomDepth);

            // Determine the X position based on the previous building in the current row
            if (!currentRowBuildings.empty()) {
                currentX += currentRowBuildings.back()->getSize().x + gap;
            }

            // Determine the Z position based on the corresponding building in the previous row
            if (z < prevRowBuildings.size()) {
                currentZ = prevRowBuildings[z]->getPosition().z + prevRowBuildings[z]->getSize().z + gap;
            }

            glm::vec3 pos = glm::vec3(currentX, m_startPos.y, currentZ);

            // Create and initialize the building
            Building* building = new Building();
            building->init();
            building->setPosition(pos);
            building->setScale(size);
            m_buildings.push_back(building);

            // Store this building in the current row
            currentRowBuildings.push_back(building);
        }

        // Move current row to previous row
        prevRowBuildings = currentRowBuildings;
        currentRowBuildings.clear();
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
void Grid::setShader(wolf::Program* shader, wolf::Program* roofShader) {
    // Set shaders
    for (auto& building : m_buildings) {
        building->setShader(shader, roofShader); 
    }
}
glm::vec3 Grid::getGridSize() const {
    float totalWidth = 0.0f;   // Total width of the grid
    float totalHeight = 0.0f;  // Maximum height in the grid
    float totalDepth = 0.0f;   // Total depth of the grid

    for (const Building* building : m_buildings) {
        glm::vec3 size = building->getSize();
        glm::vec3 pos = building->getPosition();

        // Update the total width and depth based on the building positions and sizes
        totalWidth = std::max(totalWidth, pos.x + size.x);
        totalDepth = std::max(totalDepth, pos.z + size.z);

        // Update the maximum height
        totalHeight = std::max(totalHeight, size.y);
    }

    return glm::vec3(totalWidth, totalHeight, totalDepth);
}

