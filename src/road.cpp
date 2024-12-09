#include "road.h"

const VertexRoad roadVertices[] = {
    // Top face
    { 0.0f, 0.0f, 0.0f,  0.0f, 0.0f,    0.0f, 0.0f, 1.0f}, // Bottom-left
    { 0.0f, 0.0f, 1.0f,  1.0f, 0.0f,    0.0f, 0.0f, 1.0f}, // Bottom-right
    { 1.0f, 0.0f, 1.0f,  1.0f, 1.0f,    0.0f, 0.0f, 1.0f}, // Top-right
    { 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,    0.0f, 0.0f, 1.0f} // Top-left
};
const unsigned short roadIndices[] = {
    // Top face
    0, 1, 2, 
    0, 2, 3
};

Road::Road(float lengthX, float lengthZ, const glm::vec3& startPosition)
    : m_lengthX(lengthX), m_lengthZ(lengthZ), m_startPosition(startPosition) {
    
    this->init();
    
}
Road::~Road(){
    delete m_pDecl;
    wolf::BufferManager::DestroyBuffer(m_pVB);
    wolf::BufferManager::DestroyBuffer(m_pIB);
    //destroy the texture buffer
    printf("Destroying the road");
}
void Road::init(){
    //init
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    setupBuffers();

    //Make it wrap
    m_texture = wolf::TextureManager::CreateTexture("data/textures/BenRoad.png");
    m_texture->SetFilterMode(wolf::Texture::FM_LinearMipmap, wolf::Texture::FM_LinearMipmap);
    m_texture->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, m_startPosition);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(m_lengthX, 0.01f, m_lengthZ)); // Scale the road size (Y is flat)

}
void Road::setupBuffers(){
    vertices.clear();
    for(VertexRoad vertex : roadVertices){
        vertices.push_back(vertex);
    }

    m_pVB = wolf::BufferManager::CreateVertexBuffer(vertices.data(), vertices.size() * sizeof(VertexRoad));
    m_pIB = wolf::BufferManager::CreateIndexBuffer(roadIndices, sizeof(roadIndices) / sizeof(roadIndices[0]));

    // Set up the vertex declaration
    m_pDecl = new wolf::VertexDeclaration();
    m_pDecl->Begin();
    m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
    m_pDecl->SetVertexBuffer(m_pVB);
    m_pDecl->End();
}

float Road::getLengthX() const {
    return m_lengthX;
}

float Road::getLengthZ() const {
    return m_lengthZ;
}

glm::vec3 Road::getStartPosition() const {
    return m_startPosition;
}

void Road::setLengthX(float lengthX) {
    m_lengthX = lengthX;
}

void Road::setLengthZ(float lengthZ) {
    m_lengthZ = lengthZ;
}
void Road::setSun(Sun* sun){
    if(sun != nullptr){
        m_sun = sun;
    }else{
        printf("The sun doesn't exist on the road!\n");
    }
}
void Road::setStartPosition(const glm::vec3& startPosition) {
    m_startPosition = startPosition;
}
void Road::setCamera(Camera* camera){
    if(camera != nullptr){
        m_camera = camera;
    }else{
        printf("Camera doesn't exist on road!\n");
    }
}
void Road::setShader(wolf::Program* shader){
    if(shader != 0){
        m_program = shader;
    }else{
        printf("Shader doesn't exist on road!\n");
    }
}
void Road::render(){
    
    // Get the view and projection matrices from the camera
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjMatrix();

    glm::mat4 mvp = proj * view * modelMatrix;

    m_program->Bind();

    m_program->SetUniform("mvp", mvp);
    m_program->SetUniform("worldIT", glm::transpose(glm::inverse(modelMatrix)));

    m_program->SetUniform("uScale", m_lengthZ);   //Supplying the width
    m_program->SetUniform("vScale", m_lengthX);   //supplying the height

    //lighting
    m_program->SetUniform("u_lightDir", m_sun->getLightDirection());
    m_program->SetUniform("u_lightColor", m_sun->getLightColor());
    m_program->SetUniform("u_ambientLight", m_sun->getAmbientLight());

    m_texture->Bind(0);
    m_program->SetUniform("tex", 0);

    m_pDecl->Bind();
    m_pIB->Bind();

    // Draw!
    glDrawElements(GL_TRIANGLES, sizeof(roadIndices) / sizeof(roadIndices[0]), GL_UNSIGNED_SHORT, nullptr);
    
}
