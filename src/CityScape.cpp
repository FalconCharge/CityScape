#include "CityScape.h"

CityScape::CityScape() : wolf::App("CityScape"){
    //init the camera!
    camera = new Camera(this);
    camera->init();

    this->init();
}

CityScape::~CityScape() {
    printf("Destroying the cityScape!\n");
    wolf::ProgramManager::DestroyProgram(m_plane);
    delete camera;
    delete plane1;
}

void CityScape::update(float dt) {
    if(camera){
        camera->update(dt); // Update the camera's position and state
    }
    if(this->isKeyDown(GLFW_KEY_R)){
        regenerate();
    }
    grid3d->update(dt);
}
void CityScape::init(){

    grid3d = new Grid3D(1000, 1.0f);

    //Get the shader ready
    m_plane = wolf::ProgramManager::CreateProgram("data/cube.vsh", "data/cube.fsh"); //Shader for the shader Nov.12
    m_building = wolf::ProgramManager::CreateProgram("data/building.vsh", "data/building.fsh"); //Shader for the shader Nov.12


    //Setup the plane
    plane1 = new Plane();
    plane1->setShader(m_building);
    plane1->setCamera(camera);
    plane1->setScale(glm::vec3(50.0f, 0.0f, 50.0f));
    regenerate();

    printf("initilized the city!\n");
}

void CityScape::render() {

    // Clear the screen
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(plane1) plane1->render();
    for (auto& grid : grids) {
        grid->render();
    }
    grid3d->render(camera->getViewMatrix(), camera->getProjMatrix(800, 800));
   
}
void CityScape::regenerate(){
    grids.clear();
    createGrid();
}
/*
void CityScape::createGrid(){

    grids.clear();
    grid1 = new Grid(10, 10, glm::vec3(0.0f, 0.0f, 0.0f));
    grids.push_back(grid1);

    for (auto& grid : grids) {
        // Initialize the grid
        grid->init();
        grid->setCamera(camera);
        grid->setShader(m_building);
    }
}*/
void CityScape::createGrid() {
    grids.clear();

    float gridGap = 2.0f; // Gap between grids
    int gridRows = 10;     // Number of rows per grid
    int gridCols = 10;     // Number of columns per grid
    glm::vec3 initialPosition(0.0f, 0.0f, 0.0f); // Starting position for the first grid

    // Create the first grid to calculate its size
    Grid* firstGrid = new Grid(gridRows, gridCols, initialPosition);
    firstGrid->init();
    glm::vec3 gridSize = firstGrid->getGridSize(); // Calculate the size of a single grid

    // Push the first grid to the list
    grids.push_back(firstGrid);

    // Use nested loops to create the remaining grids
    for (int x = 0; x < 2; ++x) { // 2 grids along the x-axis
        for (int z = 0; z < 2; ++z) { // 2 grids along the z-axis
            // Skip (0, 0) since the first grid is already created
            if (x == 0 && z == 0) continue;

            // Calculate the starting position of the new grid
            glm::vec3 position = initialPosition + glm::vec3(x * (gridSize.x + gridGap), 0.0f, z * (gridSize.z + gridGap));

            // Create the new grid and add it to the list
            Grid* grid = new Grid(gridRows, gridCols, position);
            grids.push_back(grid);
        }
    }

    // Initialize all grids
    for (auto& grid : grids) {
        grid->init();
        grid->setCamera(camera);
        grid->setShader(m_building);
    }

    std::cout << "Created " << grids.size() << " grids." << std::endl;
}




