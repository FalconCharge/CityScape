#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"

struct VertexBuilding
{
	GLfloat x,y,z;
    GLfloat u,v;
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
    void setColor(glm::vec3 color);
    void setPosition(glm::vec3 pos);
    void setScale(glm::vec3 scale);


private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    wolf::Texture* m_texture;           // Texture for the building
    Camera* m_camera = nullptr;         // Pointer to the camera


    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::mat4 mWorld;

    void generateVertices();
    std::vector<VertexBuilding> vertices;
};
