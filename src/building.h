#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"

struct VertexBuilding
{
	GLfloat x,y,z;
};

class Building {
public:
    glm::vec3 position;   // Position of the building (x, y, z)
    glm::vec3 size;       // Dimensions (width, height, depth)
    
    Building(glm::vec3 position, glm::vec3 size);
    ~Building();
    //void update(dt); Not nessary for a building typically
    void render();
    void init();
    void setCamera(Camera* camera);
    void setShader(wolf::Program* m_program);

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    Camera* m_camera = nullptr; // Pointer to the camera

    void generateVertices();
    std::vector<VertexBuilding> vertices;
};
