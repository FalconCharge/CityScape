#include "plane.h"


const VertexPlane planeVertices[] = {
    // Positions               // Texture Coordinates
    {  0.0f,  0.0f,  0.0f,     0.0f, 0.0f },  // Bottom-left
    {  0.0f,  0.0f,  1.0f,     1.0f, 0.0f },  // Bottom-right
    {  1.0f,  0.0f,  1.0f,     1.0f, 1.0f },  // Top-right

    {  0.0f,  0.0f,  0.0f,     0.0f, 0.0f },  // Bottom-left
    {  1.0f,  0.0f,  1.0f,     1.0f, 1.0f },  // Top-right
    {  1.0f,  0.0f,  0.0f,     0.0f, 1.0f },  // Top-left
};
Plane::Plane(){
    
}
Plane::~Plane() {
    printf("Destroying The Plane\n");
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_VBplane);
    wolf::TextureManager::DestroyTexture(m_texture);
}
void Plane::init(wolf::Program* shader, Camera* camera) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    generateVertices();
    setCamera(camera);
    setShader(shader);


    // Create vertex buffer and vertex declaration internally within Plane
    m_VBplane = wolf::BufferManager::CreateVertexBuffer(vertices.data(), vertices.size() * sizeof(VertexPlane));

    // Set up vertex declaration
    m_pDecl = new wolf::VertexDeclaration();
    m_pDecl->Begin();
    m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    m_pDecl->SetVertexBuffer(m_VBplane);
    m_pDecl->End();    

    m_texture = wolf::TextureManager::CreateTexture("data/textures/grasstop.png");
    m_texture->SetFilterMode(wolf::Texture::FM_Linear, wolf::Texture::FM_LinearMipmap);
    m_texture->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);


    //printf("Successfully initialized Plane\n");
}
void Plane::setCamera(Camera* camera){
    if(camera != nullptr){
        m_camera = camera;
    }else{
        printf("Camera doesnt exist\n");
    }
}
void Plane::setShader(wolf::Program* m_program){
    if(m_program != 0){
        m_pProgram = m_program;
    }else{
        printf("Plane Shader doesn't exist\n");
    }
}
void Plane::setPosition(glm::vec3 pos){
    m_World = glm::mat4(1.0f);
    m_World = glm::translate(m_World, pos); // Apply translation
}
void Plane::render()
{ 
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjMatrix();

    glm::mat4 mvp = proj * view * m_World;

    // Use shader program.
	m_pProgram->Bind();
    
	// Bind Uniforms 
    m_pProgram->SetUniform("mvp", mvp);

    m_pProgram->SetUniform("uScale", m_Scale.z);   //Supplying the width
    m_pProgram->SetUniform("vScale", m_Scale.x);   //supplying the height

    m_texture->Bind(1);
    m_pProgram->SetUniform("tex", 1);

	// Set up source data
	m_pDecl->Bind();

    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, sizeof(planeVertices) / sizeof(VertexPlane));
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






