#include "building.h"

Building::Building(glm::vec3 pos, glm::vec3 size) {
    m_position = pos;
    m_size = size;
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

    m_texture = wolf::TextureManager::CreateTexture("data/textures/bricksx64.png");


    //printf("Successfully initialized Building\n");
}
void Building::render()
{ 
    glm::mat4 mWorld(1.0f);
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjMatrix(800, 800);

    // Use shader program.
	m_pProgram->Bind();
    
	// Bind Uniforms 
    m_pProgram->SetUniform("projection", proj); 
    m_pProgram->SetUniform("view", view);
    m_pProgram->SetUniform("world", mWorld);

    m_texture->Bind(0);
    m_pProgram->SetUniform("tex", 0);

	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void Building::generateVertices() {
    vertices.clear();

    float x = m_position.x;
    float y = m_position.y;
    float z = m_position.z;
    float width = m_size.x;
    float height = m_size.y;
    float depth = m_size.z;

    // Helper lambda to add a vertex with position and texture coordinates
    auto addVertex = [&](float px, float py, float pz, float u, float v) {
        VertexBuilding vtx = {px, py, pz, u, v};
        vertices.push_back(vtx);
    };

    // Front face (facing positive Z direction) 
    addVertex(x, y, z, 0.0f, 0.0f);                     // Bottom-left corner
    addVertex(x + width, y, z, 1.0f, 0.0f);             // Bottom-right corner
    addVertex(x + width, y + height, z, 1.0f, 1.0f);    // Top-right corner

    addVertex(x, y, z, 0.0f, 0.0f);                     // Bottom-left corner (again, for the second triangle)
    addVertex(x + width, y + height, z, 1.0f, 1.0f);    // Top-right corner
    addVertex(x, y + height, z, 0.0f, 1.0f);            // Top-left corner

    // Back face
    addVertex(x, y, z - depth, 1.0f, 0.0f);
    addVertex(x + width, y, z - depth, 0.0f, 0.0f);
    addVertex(x + width, y + height, z - depth, 0.0f, 1.0f);

    addVertex(x, y, z - depth, 1.0f, 0.0f);
    addVertex(x + width, y + height, z - depth, 0.0f, 1.0f);
    addVertex(x, y + height, z - depth, 1.0f, 1.0f);

    // Left face
    addVertex(x, y, z, 0.0f, 0.0f);
    addVertex(x, y, z - depth, 1.0f, 0.0f);
    addVertex(x, y + height, z - depth, 1.0f, 1.0f);

    addVertex(x, y, z, 0.0f, 0.0f);
    addVertex(x, y + height, z - depth, 1.0f, 1.0f);
    addVertex(x, y + height, z, 0.0f, 1.0f);

    // Right face
    addVertex(x + width, y, z, 1.0f, 0.0f);
    addVertex(x + width, y, z - depth, 0.0f, 0.0f);
    addVertex(x + width, y + height, z - depth, 0.0f, 1.0f);

    addVertex(x + width, y, z, 1.0f, 0.0f);
    addVertex(x + width, y + height, z - depth, 0.0f, 1.0f);
    addVertex(x + width, y + height, z, 1.0f, 1.0f);

    // Top face
    addVertex(x, y + height, z, 0.0f, 0.0f);
    addVertex(x + width, y + height, z, 1.0f, 0.0f);
    addVertex(x + width, y + height, z - depth, 1.0f, 1.0f);

    addVertex(x, y + height, z, 0.0f, 0.0f);
    addVertex(x + width, y + height, z - depth, 1.0f, 1.0f);
    addVertex(x, y + height, z - depth, 0.0f, 1.0f);

    // Bottom face
    addVertex(x, y, z, 0.0f, 1.0f);
    addVertex(x + width, y, z, 1.0f, 1.0f);
    addVertex(x + width, y, z - depth, 1.0f, 0.0f);

    addVertex(x, y, z, 0.0f, 1.0f);
    addVertex(x + width, y, z - depth, 1.0f, 0.0f);
    addVertex(x, y, z - depth, 0.0f, 0.0f);
    
}
