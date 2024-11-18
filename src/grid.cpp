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

    float rowGap = 1.0f;  // Horizontal spacing
    float colGap = 1.0f;  // Vertical spacing

    // Loop to generate buildings in a grid pattern
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {

            // Generate random number between 1 and 4
            int randomHeight = std::rand() % 8 + 1;

            // Generate random color components between 0 and 1 for RGB
            float randomRed = static_cast<float>(std::rand()) / RAND_MAX;
            float randomGreen = static_cast<float>(std::rand()) / RAND_MAX;
            float randomBlue = static_cast<float>(std::rand()) / RAND_MAX;

            glm::vec3 randomColor(randomRed, randomGreen, randomBlue);

            glm::vec3 pos = m_startPos + glm::vec3(i * (m_buildingSize.x + rowGap), 0.0f, j * (m_buildingSize.z + colGap));
            glm::vec3 randomBuildingSize = glm::vec3(m_buildingSize.x, randomHeight, m_buildingSize.z);

            Building* building = new Building(pos, randomBuildingSize);
            building->init();
            //building->setColor(randomColor);
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
    for (auto building : m_buildings) {
        building->setCamera(camera);  // Set camera for each building
    }
}

void Grid::setShader(wolf::Program* shader) {
    for (auto building : m_buildings) {
        building->setShader(shader);  // Set shader for each building
    }
}

glm::vec3 Grid::getSize() const{
    // The grid's size is the number of rows/columns times the size of each building
    return glm::vec3(m_rows * m_buildingSize.x, m_buildingSize.y, m_cols * m_buildingSize.z);
}
