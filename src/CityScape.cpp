#include "CityScape.h"

CityScape::CityScape() : wolf::App("CityScape"){
    //init the camera!
    camera = new Camera(this);
    camera->init();
    camera->setScreenSize(getScreenSize());

    this->init();

    glEnable(GL_CULL_FACE); //Doesn't render the inside faces
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS); // Ensure fragments closer to the camera are drawn

}

CityScape::~CityScape() {
    printf("Destroying the cityScape!\n");
    wolf::ProgramManager::DestroyProgram(m_plane);
    wolf::ProgramManager::DestroyProgram(m_building);
    wolf::ProgramManager::DestroyProgram(m_buildingRoof);
    wolf::ProgramManager::DestroyProgram(m_road);
    wolf::ProgramManager::DestroyProgram(m_default);
    delete camera;
}

void CityScape::update(float dt) {
    if(camera){
        camera->update(dt); // Update the camera's position and state
    }
    if(this->isKeyDown(GLFW_KEY_R)){
        regenerate();       //If "R" is pressed regenerate the city
    }
    if(sun){
        sun->update(dt);    //Sun movement
    }
    
}
void CityScape::init(){

    //grid3d = new Grid3D(1000, 1.0f);    //Create a grid for debugging
    sun = new Sun();

    //Get the shaders ready
    m_plane = wolf::ProgramManager::CreateProgram("data/plane.vsh", "data/default.fsh"); //Shader for the shader Nov.12
    m_building = wolf::ProgramManager::CreateProgram("data/building.vsh", "data/default.fsh"); //Shader for the shader Nov.12
    m_buildingRoof = wolf::ProgramManager::CreateProgram("data/buildingRoof.vsh", "data/default.fsh"); //Shader for the shader Nov.12
    m_road = wolf::ProgramManager::CreateProgram("data/road.vsh", "data/default.fsh");

    regenerate();

    printf("initilized the city!\n");
}

void CityScape::render() {

    // Clear the screen
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //grid3d->render(camera->getViewMatrix(), camera->getProjMatrix());   //Render the 3D grid for debugging

    for (auto& grid : grids) {
        grid->render();
    }
    for(auto& road : roads){
        road->render();
    }
    for(auto& plane : planes){
        plane->render();
    }
   
}
void CityScape::regenerate(){
    grids.clear();
    createGrid();
}
void CityScape::createGrid() {
    roads.clear();
    planes.clear();

    float gridGapX = 1.0f;   // Gap between grids
    float gridGapZ = 3.0f;   // Gap between rows
    int gridSize = 20.0f;    // Size of a single grid

    glm::vec3 initialPosition(0.0f, 0.0f, 0.0f); // Starting position for the first grid

    // Use nested loops to create the grids, roads, and planes
    for (int x = 0; x < 3; ++x) {       // 3 grids along the x-axis
        for (int z = 0; z < 3; ++z) {   // 3 grids along the z-axis
            // Calculate the starting and ending positions of the new grid
            glm::vec3 position = initialPosition + glm::vec3(x * (gridSize + gridGapX), 0.0f, z * (gridSize + gridGapZ));
            glm::vec3 endPosition = position + glm::vec3(gridSize, 0.0f, gridSize);

            // Create the grid
            Grid* grid = new Grid(position, endPosition);
            grids.push_back(grid);

            // Create a plane for this grid
            Plane* plane = new Plane();
            plane->init(m_plane, camera);
            plane->setSun(sun);
            plane->setPosition(glm::vec3(position.x - 1.0f, 0.0f, position.z -1.0f)); // Align plane to grid position
            plane->setScale(glm::vec3(gridSize + 2.0f, 1.0f, gridSize + 2.0f)); // Scale plane to grid size
            planes.push_back(plane);

            // Add a road aligned to the bottom-right of the grid
            glm::vec3 roadPosition = glm::vec3(position.x, 0.0f, position.z - gridGapZ + 1.0f); // Place road at the bottom of the grid
            Road* road = new Road(gridSize + gridGapX, 1.0f, roadPosition);
            road->setCamera(camera);
            road->setShader(m_road);
            road->setSun(sun);
            roads.push_back(road);
            
        }
    }

    // Initialize all grids
    float count = 0;
    for (auto& grid : grids) {
        grid->init();
        grid->setCameraShaderSun(camera, m_building, m_buildingRoof, sun);
        for (auto& building : grid->getBuildings()) {
            count++;
        }
    }
    printf("Amount of Buildings: %f\n", count);
    std::cout << "Created " << grids.size() << " grids, " << roads.size() << " roads, and " << planes.size() << " planes." << std::endl;
}


