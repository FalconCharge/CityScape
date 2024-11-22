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
void CityScape::createGrid(){

    grids.clear();
    grid1 = new Grid(5, 5, glm::vec3(0.0f, 0.0f, 0.0f));
    grids.push_back(grid1);

    for (auto& grid : grids) {
        // Initialize the grid
        grid->init();
        grid->setCamera(camera);
        grid->setShader(m_building);
    }
}
void CityScape::createFakeGrid(){
    fakeGrid = new FakeGrid(100.0f, 100.0f, 2.0f);
}

