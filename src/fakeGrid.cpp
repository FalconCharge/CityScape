#include "FakeGrid.h"
#include <iostream>
#include <cstdlib> // For std::rand()

// Constructor to initialize the grid with all cells available (1)
FakeGrid::FakeGrid(int rows, int cols) : m_rows(rows), m_cols(cols) {
    m_grid = std::vector<std::vector<int>>(m_rows, std::vector<int>(m_cols, 1)); // Initialize all cells as available
}

// Method to print the grid for debugging
void FakeGrid::printGrid() const {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            std::cout << m_grid[i][j] << " "; // 1 means available, 0 means occupied
        }
        std::cout << "\n";
    }
}

// Method to place a building in the grid
bool FakeGrid::placeBuilding(int startRow, int startCol, Building* building) {
    // Get the size of the building (using glm::vec3)
    glm::vec3 size = building->getSize();

    // Check if the building can fit in the space (considering width and depth)
    for (int i = startRow; i < startRow + size.x; ++i) {
        for (int j = startCol; j < startCol + size.z; ++j) {
            // Check bounds and if the space is available
            if (i >= m_rows || j >= m_cols || m_grid[i][j] == 0) {
                return false;  // Building can't fit here
            }
        }
    }

    // Place the building (mark cells as unavailable)
    for (int i = startRow; i < startRow + size.x; ++i) {
        for (int j = startCol; j < startCol + size.z; ++j) {
            m_grid[i][j] = 0;  // Mark as occupied
        }
    }

    return true;  // Building was placed successfully
}
