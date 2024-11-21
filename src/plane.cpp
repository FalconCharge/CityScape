#include "plane.h"


const VertexPlane planeVertices[] = {
    // Positions               // Texture Coordinates
    {  0.0f,  0.0f,  0.0f,     0.0f, 0.0f },  // Bottom-left
    {  1.0f,  0.0f,  0.0f,     1.0f, 0.0f },  // Bottom-right
    {  1.0f,  0.0f,  1.0f,     1.0f, 1.0f },  // Top-right

    {  0.0f,  0.0f,  0.0f,     0.0f, 0.0f },  // Bottom-left
    {  1.0f,  0.0f,  1.0f,     1.0f, 1.0f },  // Top-right
    {  0.0f,  0.0f,  1.0f,     0.0f, 1.0f },  // Top-left
};
Plane::Plane(){
    this->init();
}
Plane::~Plane() {
    printf("Destroying The Plane\n");
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
    wolf::TextureManager::DestroyTexture(m_texture);
}
void Plane::init() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //Generate vertices Based on subdivisions
    generateVertices();

    m_pVB = wolf::BufferManager::CreateVertexBuffer(vertices.data(), vertices.size() * sizeof(VertexPlane));

    // Set up the vertex declaration
    m_pDecl = new wolf::VertexDeclaration();
    m_pDecl->Begin();
    m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    m_pDecl->SetVertexBuffer(m_pVB);
    m_pDecl->End();

    
    m_texture = wolf::TextureManager::CreateTexture("data/textures/grasstop.png");
    m_texture->SetFilterMode(wolf::Texture::FM_Linear, wolf::Texture::FM_LinearMipmap);
    m_texture->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

    printf("Successfully initialized Plane\n");
}
void Plane::setCamera(Camera* camera){
    if(camera){
        m_camera = camera;
    }else{
        printf("Camera doesnt exist\n");
    }
}
void Plane::setShader(wolf::Program* m_program){
    m_pProgram = m_program;
}
void Plane::render()
{ 
    
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjMatrix(800, 800);

    // Use shader program.
	m_pProgram->Bind();
    

	// Bind Uniforms 
    m_pProgram->SetUniform("projection", proj); 
    m_pProgram->SetUniform("view", view);
    m_pProgram->SetUniform("world", m_World);

    m_pProgram->SetUniform("uScale", m_Scale.z);   //Supplying the width
    m_pProgram->SetUniform("vScale", m_Scale.x);   //supplying the height

    m_texture->Bind(1);
    m_pProgram->SetUniform("tex", 1);

	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void Plane::generateVertices() {
    vertices.clear();
    for(VertexPlane vertex : planeVertices){
        vertices.push_back(vertex);
    }
}
void Plane::setScale(glm::vec3 scale){
    m_Scale = scale;
    m_World = glm::scale(m_World, m_Scale); // Apply scale
}





