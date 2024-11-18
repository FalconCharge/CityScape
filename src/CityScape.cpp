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
    if(plane1){
        plane1->update(dt);
    }
}
void CityScape::init(){
    //Get the shader ready
    m_plane = wolf::ProgramManager::CreateProgram("data/cube.vsh", "data/cube.fsh"); //Shader for the shader Nov.12
    m_building = wolf::ProgramManager::CreateProgram("data/building.vsh", "data/building.fsh"); //Shader for the shader Nov.12


    //Setup the plane
    plane1 = new Plane(1);
    plane1->init(m_plane);
    plane1->setCamera(camera);

    
    //Makeing 1 buildilng to add the texture somehow
    building1 = new Building(glm::vec3(-3.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    building1->init();
    building1->setCamera(camera);
    building1->setShader(m_building);
    
    
    
    grid1 = new Grid(10, 10, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    grids.push_back(grid1);

    glm::vec3 grid1Size = grid1->getSize();

    grids.push_back(new Grid(10, 10, glm::vec3(0.0f, 0.0f, -grid1Size.z - 10.0f), glm::vec3(0.5f, 1.0f, 0.5f)));
    grids.push_back(new Grid(10, 10, glm::vec3(-grid1Size.x-11.0f, 0.0f, -grid1Size.z - 10.0f), glm::vec3(0.5f, 1.0f, 0.5f)));
    grids.push_back(new Grid(10, 10, glm::vec3(-grid1Size.x - 11.0f, 0.0f, 0.0f), glm::vec3(0.5f, 1.0f, 0.5f)));

    // Iterate through all grids in the grids vector
    for (auto& grid : grids) {
        // Initialize the grid
        grid->init();
        grid->setCamera(camera);
        grid->setShader(m_building);
    }
    


    printf("initilized the city!\n");
}

void CityScape::render() {

    // Clear the screen
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(plane1) plane1->render();
    if(building1) building1->render();

    for (auto& grid : grids) {
        grid->render();
    }
   
}


