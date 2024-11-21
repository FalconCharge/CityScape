#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"
#include "building.h"


class FakeGrid {
public:
    // Constructor to initialize the grid size
    FakeGrid(int rows, int cols);

    // Method to print the current state of the grid
    void printGrid() const;

    // Method to try placing a building at the specified position
    bool placeBuilding(int startRow, int startCol, Building* building);

private:
    int m_rows;               // Number of rows in the grid
    int m_cols;               // Number of columns in the grid
    std::vector<std::vector<int>> m_grid;  // 1 = available, 0 = unavailable
};

