#include "plane.h"
#include "../samplefw/Grid2D.h"


Vertex gs_squareVertices[] = {
    // Triangle 1
    {-1.0f, -1.0f, 0.0f},  // Bottom-left
    {1.0f, -1.0f, 0.0f},   // Bottom-right
    {-1.0f, 1.0f, 0.0f},    // Top-left

    // Triangle 2
    {1.0f, -1.0f, 0.0f},    // Bottom-right
    {1.0f, 1.0f, 0.0f},     // Top-right
    {-1.0f, 1.0f, 0.0f}     // Top-left
};




// Destructor
Plane::~Plane() {
    printf("Destroying The Plane\n");
    delete m_pDecl;
    wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
}
void Plane::setShader(wolf::Program* m_program){
    m_pProgram = m_program;
}

void Plane::init() {
    // Only initialize if it hasn't been done already
    if (!m_pProgram) {
        // Set pixel storage mode
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        //Generate vertices Based on subdivisions
        generateVertices();

        // Load and compile shader program
        m_pProgram = wolf::ProgramManager::CreateProgram("data/planeWater.vsh", "data/planeWater.fsh");

        m_pVB = wolf::BufferManager::CreateVertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex));

        // Set up the vertex declaration
        m_pDecl = new wolf::VertexDeclaration();
        m_pDecl->Begin();
        m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        m_pDecl->SetVertexBuffer(m_pVB);
        m_pDecl->End();
    }

    m_time = 0.0f;
    printf("Successfully initialized Plane\n");
}

void Plane::render(glm::mat4& view, glm::mat4& projection)
{ 
    
    glm::mat4 mWorld(1.0f);

    // Use shader program.
	m_pProgram->Bind();
    
	// Bind Uniforms
    m_pProgram->SetUniform("projection", projection);
    m_pProgram->SetUniform("view", view);
    m_pProgram->SetUniform("world", mWorld);

    m_pProgram->SetUniform("time", m_time);

    m_pProgram->SetUniform("u_color1", glm::vec4(0.0f, 0.5f, 1.0f, 1.0f)); // Lighter blue
    m_pProgram->SetUniform("u_color2", glm::vec4(0.0f, 0.0f, 0.5f, 1.0f)); // Darker blue

    
	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void Plane::update(float dt){
    m_time += dt;
}
void Plane::render(int height, int width){
    return;
}

void Plane::generateVertices() {
    if (subdivisions <= 0) {
        printf("Subdivisions must be greater than 0.\n");
        return; // Exit the function if subdivisions are not valid
    }

    vertices.clear();
    float size = 5.0f; // Size of each plane
    float step = size / subdivisions; // Calculate the distance between each vertex

    // Nested loop to generate subdivisions
    for (int i = 0; i < subdivisions; ++i) {
        for (int j = 0; j < subdivisions; ++j) {

            // Calculate the offset for centering the plane
            float xOffset = j * step - (size / 2.0f); // Center the plane on x-axis
            float zOffset = i * step - (size / 2.0f); // Center the plane on z-axis

            // Define the four corners of the quad on the x-z plane
            Vertex v0 = { xOffset, 0.0f, zOffset };                       // Bottom-left
            Vertex v1 = { xOffset + step, 0.0f, zOffset };              // Bottom-right
            Vertex v2 = { xOffset, 0.0f, zOffset + step };              // Top-left
            Vertex v3 = { xOffset + step, 0.0f, zOffset + step };       // Top-right

            // First triangle
            vertices.push_back(v0); // Bottom-left
            vertices.push_back(v1); // Bottom-right
            vertices.push_back(v2); // Top-left

            // Second triangle
            vertices.push_back(v1); // Bottom-right
            vertices.push_back(v3); // Top-right
            vertices.push_back(v2); // Top-left
        }
    }

    printf("Generate vertices\n");
    printf("Generated %zu vertices\n", vertices.size());
}






