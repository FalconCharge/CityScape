#include "grid.h"

void Grid::generate() {
    buildings.clear();
    //std::srand(std::time(nullptr)); // Seed for randomization

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            glm::vec3 position = glm::vec3(col * cellSize, 0.0f, row * cellSize);
            glm::vec3 size = glm::vec3(
                (std::rand() % 3 + 1) * 2.0f, // Random width (multiple of 2)
                (std::rand() % 10 + 5) * 1.0f, // Random height
                (std::rand() % 3 + 1) * 2.0f  // Random depth
            );
            //buildings.emplace_back(position, size, 0); // Add building with default texture
        }
    }
}

