#include "CityScape.h"

CityScape::CityScape() : wolf::App("CityScape"){
    //init the camera!
    camera = new Camera(this);
    camera->init();

    this->init();

    glEnable(GL_CULL_FACE); //Doesn't render the inside faces
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
    m_plane = wolf::ProgramManager::CreateProgram("data/plane.vsh", "data/plane.fsh"); //Shader for the shader Nov.12
    m_building = wolf::ProgramManager::CreateProgram("data/building.vsh", "data/building.fsh"); //Shader for the shader Nov.12
    m_buildingRoof = wolf::ProgramManager::CreateProgram("data/buildingRoof.vsh", "data/building.fsh"); //Shader for the shader Nov.12

    m_default = wolf::ProgramManager::CreateProgram("data/default.vsh", "data/default.fsh");

    //Setup the plane
    plane1 = new Plane();
    plane1->setShader(m_plane);
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
void CityScape::createGrid() {
    grids.clear();

    float gridGap = 3.0f; // Gap between grids
    int gridSize = 20.0f;   //Used to define how much the grid expands in the x or z

    glm::vec3 initialPosition(0.0f, 0.0f, 0.0f); // Starting position for the first grid
    glm::vec3 endPosition = glm::vec3(initialPosition.x + gridSize, initialPosition.y, initialPosition.z + gridSize);

    // Create the first grid to calculate its size
    Grid* firstGrid = new Grid(initialPosition, endPosition);
    firstGrid->init();

    glm::vec3 gridFinalSize = firstGrid->getGridSize(); // Calculate the size of a single grid

    // Push the first grid to the list
    grids.push_back(firstGrid);
    
    // Use nested loops to create the remaining grids
    for (int x = 0; x < 2; ++x) { // 2 grids along the x-axis
        for (int z = 0; z < 2; ++z) { // 2 grids along the z-axis
            // Skip (0, 0) since the first grid is already created
            if (x == 0 && z == 0) continue;

            // Calculate the starting position of the new grid
            glm::vec3 position = initialPosition + glm::vec3(x * (gridFinalSize.x + gridGap), 0.0f, z * (gridFinalSize.z + gridGap));
            glm::vec3 endPos = glm::vec3(position.x + gridSize, position.y, position.z + gridSize);

            // Create the new grid and add it to the list
            Grid* grid = new Grid(position, endPos);
            grids.push_back(grid);
        }
    }
    float count = 0;
    // Initialize all grids
    for (auto& grid : grids) {
        grid->init();
        grid->setCamera(camera);
        grid->setShader(m_building, m_buildingRoof);
        for(auto& building : grid->getBuildings()){
            count++;
        }
        printf("Amount of Buildings is %f \n", count);
    }

    std::cout << "Created " << grids.size() << " grids." << std::endl;
}




