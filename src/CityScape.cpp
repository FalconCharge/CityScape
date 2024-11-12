#include "CityScape.h"

CityScape::CityScape() : wolf::App("CityScape"){
    //init the camera!
    camera = new Camera(this);
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
    m_plane = wolf::ProgramManager::CreateProgram("data/planeWater.vsh", "data/planeWater.fsh");

    plane1 = new Plane(5);
    plane1->init(m_plane);
    plane1->setCamera(camera);
    
    printf("initilized the city!\n");
}

void CityScape::render() {

    // Clear the screen
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render a plane
    plane1->render();
}
