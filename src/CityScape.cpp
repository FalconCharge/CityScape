#include "CityScape.h"

CityScape::CityScape() : wolf::App("CityScape"){
    cube1.init();
    camera = new Camera(this);
}

CityScape::~CityScape() {
    wolf::ProgramManager::DestroyProgram(m_pProgram);
    delete camera;
}

void CityScape::update(float dt) {
    camera->update(dt);  // Update the camera's position and state
}
void CityScape::init(){
    m_pProgram = wolf::ProgramManager::CreateProgram("data/cube.vsh", "data/cube.fsh");
    Cube cube1;
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

    cube1.render(view, proj);
}
