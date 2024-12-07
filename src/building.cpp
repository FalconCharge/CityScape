#include "building.h"

// Define the vertices for a cube with UV cords
const VertexBuilding cubeVertices[] = {
    // Front face
    { 0.0f, 0.0f, 1.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 0.0f, 1.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 1.0f, 1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 1.0f, 1.0f,  0.0f, 1.0f }, // Top-left

    // Back face
    { 0.0f, 0.0f, 0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 0.0f, 0.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 1.0f, 0.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 1.0f, 0.0f,  0.0f, 1.0f }, // Top-left

    // Left face
    { 0.0f, 0.0f, 0.0f,  0.0f, 0.0f }, // Bottom-left
    { 0.0f, 0.0f, 1.0f,  1.0f, 0.0f }, // Bottom-right
    { 0.0f, 1.0f, 1.0f,  1.0f, 1.0f }, // Top-right
    { 0.0f, 1.0f, 0.0f,  0.0f, 1.0f }, // Top-left

    // Right face
    { 1.0f, 0.0f, 0.0f,  0.0f, 0.0f }, // Bottom-left
    { 1.0f, 0.0f, 1.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 1.0f, 1.0f,  1.0f, 1.0f }, // Top-right
    { 1.0f, 1.0f, 0.0f,  0.0f, 1.0f }, // Top-left

    // Top face
    { 0.0f, 1.0f, 0.0f,  0.0f, 0.0f }, // Bottom-left
    { 0.0f, 1.0f, 1.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 1.0f, 1.0f,  1.0f, 1.0f }, // Top-right
    { 1.0f, 1.0f, 0.0f,  0.0f, 1.0f }, // Top-left

    // Bottom face
    { 0.0f, 0.0f, 0.0f,  0.0f, 0.0f }, // Bottom-left
    { 0.0f, 0.0f, 1.0f,  1.0f, 0.0f }, // Bottom-right
    { 1.0f, 0.0f, 1.0f,  1.0f, 1.0f }, // Top-right
    { 1.0f, 0.0f, 0.0f,  0.0f, 1.0f }  // Top-left
};
const unsigned short cubeIndices[] = {
    // Front face
    0, 1, 2,  // Triangle 1
    0, 2, 3,  // Triangle 2

    // Back face
    4, 6, 5,    //Triangle 1
    4, 7, 6,    //Triangle 2

    //left face
    8, 9, 10, // Triangle 1
    8, 10, 11, // Triangle 2    

    // Right face
    12, 14, 13, // Triangle 1
    12, 15, 14, // Triangle 2

    // Top face
    16, 17, 18, // Triangle 1
    16, 18, 19, // Triangle 2
};
const unsigned short wallIndices[] = {
    // Front face
    0, 1, 2,  // Triangle 1
    0, 2, 3,  // Triangle 2

    // Back face
    4, 6, 5,    //Triangle 1
    4, 7, 6,    //Triangle 2

    //left face
    8, 9, 10, // Triangle 1
    8, 10, 11, // Triangle 2    

    // Right face
    12, 14, 13, // Triangle 1
    12, 15, 14, // Triangle 2
};
const unsigned short roofIndices[] = {
    // Top face
    16, 17, 18, // Triangle 1
    16, 18, 19, // Triangle 2
};

Building::~Building(){
    printf("Destroying The Building\n");
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
    wolf::TextureManager::DestroyTexture(m_texture);
    wolf::TextureManager::DestroyTexture(m_rooftexture);
    wolf::BufferManager::DestroyBuffer(m_pIB);
    wolf::BufferManager::DestroyBuffer(m_pIBR);
}
void Building::setCamera(Camera* camera){
    m_camera = camera;
}
void Building::setShader(wolf::Program* m_program, wolf::Program* roofShader){
    m_pProgram = m_program;
    m_roofShader = roofShader;
}
void Building::setColor(glm::vec3 color){
    m_color = color;
}
void Building::setPosition(glm::vec3 pos){
    m_position = pos;
    mWorld = glm::mat4(1.0f);
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

    // Create the index buffer
    m_pIB = wolf::BufferManager::CreateIndexBuffer(wallIndices, sizeof(wallIndices) / sizeof(wallIndices[0]));
    m_pIBR = wolf::BufferManager::CreateIndexBuffer(roofIndices, sizeof(roofIndices) / sizeof(roofIndices[0]));

    // Set up the vertex declaration
    m_pDecl = new wolf::VertexDeclaration();
    m_pDecl->Begin();
    m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    m_pDecl->SetVertexBuffer(m_pVB);
    m_pDecl->End();

    //Make it wrap
    m_texture = wolf::TextureManager::CreateTexture("data/textures/BenWallWindows.png");
    m_texture->SetFilterMode(wolf::Texture::FM_LinearMipmap, wolf::Texture::FM_LinearMipmap);
    m_texture->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

    m_rooftexture = wolf::TextureManager::CreateTexture("data/textures/BenRoof.png");
    m_rooftexture->SetFilterMode(wolf::Texture::FM_LinearMipmap, wolf::Texture::FM_LinearMipmap);
    m_rooftexture->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

    // Initialize transformation matrix
    mWorld = glm::mat4(1.0f);

}
void Building::render()
{ 
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjMatrix(800, 800);

    glm::mat4 mvp = proj * view * mWorld;

    // Use shader program.
	m_pProgram->Bind();
    
	// Bind Uniforms 
    m_pProgram->SetUniform("mvp", mvp);

    m_pProgram->SetUniform("uScale", m_scale.x);   //Supplying the width
    m_pProgram->SetUniform("vScale", m_scale.y);   //supplying the height

    m_texture->Bind(0);                     //Supply the texture and bind it
    m_pProgram->SetUniform("tex", 0);

	// Set up source data
	m_pDecl->Bind();
    m_pIB->Bind();

    // Draw!
    glDrawElements(GL_TRIANGLES, sizeof(wallIndices) / sizeof(wallIndices[0]), GL_UNSIGNED_SHORT, nullptr);

    m_roofShader->Bind();

    // Bind Uniforms 
    m_roofShader->SetUniform("mvp", mvp);

    m_roofShader->SetUniform("uScale", m_scale.z);   //Supplying the width
    m_roofShader->SetUniform("vScale", m_scale.x);   //supplying the length

    m_rooftexture->Bind(0);
    m_roofShader->SetUniform("tex", 0);

    m_pDecl->Bind();
    m_pIBR->Bind();

    glDrawElements(GL_TRIANGLES, sizeof(roofIndices) / sizeof(roofIndices[0]), GL_UNSIGNED_SHORT, nullptr);

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
glm::vec3 Building::getPosition() const{
    return m_position;
}






