#include "building.h"

// Define the vertices for a cube with positive coordinates
const VertexBuilding cubeVertices[] = {
    // Front face
    { 0.0f, 0.0f,  1.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 0.0f,  1.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 1.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 0.0f,  1.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 1.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 1.0f,  1.0f,  0.0f, 1.0f }, // Top-left

    // Back face
    { 0.0f, 0.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 0.0f,  0.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 1.0f,  0.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 0.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 1.0f,  0.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 1.0f,  0.0f,  0.0f, 1.0f }, // Top-left

    // Left face
    { 0.0f, 0.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 0.0f, 0.0f,  1.0f,  1.0f, 0.0f }, // Bottom-right
    { 0.0f, 1.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 0.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 0.0f, 1.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 1.0f,  0.0f,  0.0f, 1.0f }, // Top-left

    // Right face
    { 1.0f, 0.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 0.0f,  1.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 1.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 1.0f, 0.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 1.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 1.0f, 1.0f,  0.0f,  0.0f, 1.0f }, // Top-left

    // Top face
    { 0.0f, 1.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 1.0f,  0.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 1.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 1.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 1.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 1.0f,  1.0f,  0.0f, 1.0f }, // Top-left

    // Bottom face
    { 0.0f, 0.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 0.0f,  0.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 0.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 0.0f,  0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 0.0f,  1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 0.0f,  1.0f,  0.0f, 1.0f }  // Top-left
};


Building::Building(glm::vec3 pos, glm::vec3 size) {
    m_position = pos;
    m_scale = size;
}
Building::~Building(){
    printf("Destroying The Building\n");
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
    wolf::TextureManager::DestroyTexture(m_texture);
}
void Building::setCamera(Camera* camera){
    m_camera = camera;
}
void Building::setShader(wolf::Program* m_program){
    m_pProgram = m_program;
}
void Building::setColor(glm::vec3 color){
    m_color = color;
}
void Building::setPosition(glm::vec3 pos){
    m_position = pos;
    mWorld = glm::translate(mWorld, m_position); // Apply translation
}
void Building::setScale(glm::vec3 scale){
    m_scale = scale;
    mWorld = glm::scale(mWorld, scale); // Apply scale
}
void Building::init(){
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //Generate vertices
    generateVertices();

    m_pVB = wolf::BufferManager::CreateVertexBuffer(vertices.data(), vertices.size() * sizeof(VertexBuilding));

    // Set up the vertex declaration
    m_pDecl = new wolf::VertexDeclaration();
    m_pDecl->Begin();
    m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    m_pDecl->SetVertexBuffer(m_pVB);
    m_pDecl->End();

    //Make it wrap
    m_texture = wolf::TextureManager::CreateTexture("data/textures/BenWall.png");
    m_texture->SetFilterMode(wolf::Texture::FM_Linear, wolf::Texture::FM_LinearMipmap);
    m_texture->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

    // Initialize transformation matrix
    mWorld = glm::mat4(1.0f);
    mWorld = glm::scale(mWorld, glm::vec3(m_scale.x, m_scale.y, m_scale.z));                        // Apply scale
    mWorld = glm::translate(mWorld, glm::vec3(m_position.x, m_position.y * 2.0f, m_position.z));    // Apply translation

    uScale = m_scale.x;
    vScale = m_scale.y;

}
void Building::render()
{ 
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjMatrix(800, 800);

    // Use shader program.
	m_pProgram->Bind();
    
	// Bind Uniforms 
    m_pProgram->SetUniform("projection", proj); 
    m_pProgram->SetUniform("view", view);
    m_pProgram->SetUniform("world", mWorld);

    m_pProgram->SetUniform("uScale", uScale);   //Supplying the width
    m_pProgram->SetUniform("vScale", vScale);   //supplying the height

    m_texture->Bind(0);
    m_pProgram->SetUniform("tex", 0);

	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void Building::generateVertices(){
    vertices.clear();
    for(VertexBuilding vertex : cubeVertices){
        vertices.push_back(vertex);
    }
}
glm::vec3 Building::getSize() const{
    return m_scale;
}




