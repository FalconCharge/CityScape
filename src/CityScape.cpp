#include "CityScape.h"

CityScape::CityScape() : wolf::App("CityScape"){
    camera = new Camera(this);
    camera->init();

}

CityScape::~CityScape() {
    wolf::ProgramManager::DestroyProgram(m_pProgram);
    wolf::ProgramManager::DestroyProgram(m_plane);
    delete camera;
    delete plane1;
}

void CityScape::update(float dt) {
    camera->update(dt);  // Update the camera's position and state
}
void CityScape::init(){
    m_pProgram = wolf::ProgramManager::CreateProgram("data/cube.vsh", "data/cube.fsh");
    m_plane =  wolf::ProgramManager::CreateProgram("data/planeWater.vsh", "data/planeWater.fsh");

    plane1 = new Plane(5);
    plane1->setShader(m_plane);
}

void CityScape::render() {
    // Get the camera matrices
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 proj = camera->getProjMatrix(800, 800);

    // Clear the screen
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    // Bind the shader program
    m_pProgram->Bind();

    // Set uniform matrices in the shader
    m_pProgram->SetUniform("view", view);
    m_pProgram->SetUniform("projection", proj);

    // Bind the plane shader program
    m_plane->Bind();
    m_plane->SetUniform("view", view);
    m_plane->SetUniform("projection", proj);

    plane1->render(view, proj);

}
