#include "plane.h"


// Destructor
Plane::~Plane() {
    printf("Destroying The Plane\n");
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
    //glDeleteTextures(1, &m_tex);
}

//On init takes in the shader program to use
void Plane::init(wolf::Program* m_program) {
    m_pProgram = m_program;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //Generate vertices Based on subdivisions
    generateVertices();

    m_pVB = wolf::BufferManager::CreateVertexBuffer(vertices.data(), vertices.size() * sizeof(VertexPlane));

    // Set up the vertex declaration
    m_pDecl = new wolf::VertexDeclaration();
    m_pDecl->Begin();
    m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    //m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    m_pDecl->SetVertexBuffer(m_pVB);
    m_pDecl->End();

    m_time = 0.0f;

    //loadTexture("data/grasstop.png");
    //wolf::Texture* pTex = wolf::TextureManager::CreateTexture("data/grasstop.png");

    printf("Successfully initialized Plane\n");

}
void Plane::setCamera(Camera* camera){
    if(camera){
        m_camera = camera;
    }else{
        printf("Camera doesnt exist\n");
    }
}
void Plane::render()
{ 
    glm::mat4 mWorld(1.0f);
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjMatrix(800, 800);

    // Use shader program.
	m_pProgram->Bind();
    
    //glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_tex);

	// Bind Uniforms 
    m_pProgram->SetUniform("projection", proj); 
    m_pProgram->SetUniform("view", view);
    m_pProgram->SetUniform("world", mWorld);
    //m_pProgram->SetUniform("tex", 0);

    m_pProgram->SetUniform("time", m_time);

    

	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void Plane::update(float dt){
    m_time += dt;
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
            VertexPlane v0 = { xOffset, 0.0f, zOffset                };                       // Bottom-left
            VertexPlane v1 = { xOffset + step, 0.0f, zOffset         };              // Bottom-right
            VertexPlane v2 = { xOffset, 0.0f, zOffset + step         };              // Top-left
            VertexPlane v3 = { xOffset + step, 0.0f, zOffset + step  };       // Top-right
            /*
            // Define the four corners of the quad on the x-z plane with texture coordinates
            Vertex v0 = { xOffset,           0.0f, zOffset,           0.0f, 0.0f}; // Bottom-left
            Vertex v1 = { xOffset + step,    0.0f, zOffset,           1.0f, 0.0f}; // Bottom-right
            Vertex v2 = { xOffset,           0.0f, zOffset + step,    0.0f, 1.0f}; // Top-left
            Vertex v3 = { xOffset + step,    0.0f, zOffset + step,    1.0f, 1.0f}; // Top-right
            */

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

    printf("Generated %zu vertices\n", vertices.size());
}
void Plane::loadTexture(char* texturePath) {
    wolf::Texture* m_pTex = wolf::TextureManager::CreateTexture(texturePath);
    if (m_pTex) {
            printf("Texture loaded successfully!\n");
        } else {
            printf("Failed to load texture: %s\n", texturePath);
        }
}





