#include "building.h"

Building::Building(glm::vec3 pos, glm::vec3 size) {
    m_position = pos;
    m_size = size;
}
Building::~Building(){
    printf("Destroying The Building\n");
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
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
    m_pDecl->SetVertexBuffer(m_pVB);
    m_pDecl->End();

    printf("Successfully initialized Building\n");
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


    m_pProgram->SetUniform("u_color", m_color);

	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void Building::generateVertices(){
    vertices.clear();

    // Assuming you want to generate a cuboid (a 3D box)
    float x = m_position.x;
    float y = m_position.y;
    float z = m_position.z;
    float width = m_size.x;
    float height = m_size.y;
    float depth = m_size.z;

    // Helper lambda to add a vertex
    auto addVertex = [&](float x, float y, float z) {
        VertexBuilding v = {x, y, z}; 
        vertices.push_back(v);
    };

    // Vertices for the cuboid (building) using position and size
    // Front face
    addVertex(x, y, z); 
    addVertex(x + width, y, z); 
    addVertex(x + width, y + height, z); 

    addVertex(x, y, z); 
    addVertex(x + width, y + height, z); 
    addVertex(x, y + height, z); 

    // Back face
    addVertex(x, y, z - depth); 
    addVertex(x + width, y, z - depth); 
    addVertex(x + width, y + height, z - depth); 

    addVertex(x, y, z - depth); 
    addVertex(x + width, y + height, z - depth); 
    addVertex(x, y + height, z - depth); 

    // Left face
    addVertex(x, y, z); 
    addVertex(x, y, z - depth); 
    addVertex(x, y + height, z - depth); 

    addVertex(x, y, z); 
    addVertex(x, y + height, z - depth); 
    addVertex(x, y + height, z); 

    // Right face
    addVertex(x + width, y, z); 
    addVertex(x + width, y, z - depth); 
    addVertex(x + width, y + height, z - depth); 

    addVertex(x + width, y, z); 
    addVertex(x + width, y + height, z - depth); 
    addVertex(x + width, y + height, z); 

    // Top face
    addVertex(x, y + height, z); 
    addVertex(x + width, y + height, z); 
    addVertex(x + width, y + height, z - depth); 

    addVertex(x, y + height, z); 
    addVertex(x + width, y + height, z - depth); 
    addVertex(x, y + height, z - depth); 

    // Bottom face
    addVertex(x, y, z); 
    addVertex(x + width, y, z); 
    addVertex(x + width, y, z - depth); 

    addVertex(x, y, z); 
    addVertex(x + width, y, z - depth); 
    addVertex(x, y, z - depth); 
}
