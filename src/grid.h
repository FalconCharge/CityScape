#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"
#include "building.h"

class Grid {
public:
    int rows, cols;                       // Number of rows and columns in the grid
    float cellSize;                       // Size of each grid cell
    std::vector<Building> buildings;      // Collection of buildings in the grid
    
    Grid(int rows, int cols, float cellSize);
    void generate();                      // Randomly generate building placements
    void render(glm::mat4& view, glm::mat4& projection);
};
