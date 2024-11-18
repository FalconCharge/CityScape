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

    grid = new Grid(10, 10, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 1.0f, 0.5f));
    grid->init();

    grid->setCamera(camera);
    grid->setShader(m_building);

    /*//Set up the building
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 size = glm::vec3(1.0f, 3.0f, 1.0f);
    building1 = new Building(pos, size);
    building1->init();
    building1->setCamera(camera);
    building1->setShader(m_building);
    */

    printf("initilized the city!\n");
}

void CityScape::render() {

    // Clear the screen
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(plane1) plane1->render();
    if(grid) grid->render();

    
}


