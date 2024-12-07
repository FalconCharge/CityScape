#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"

struct VertexPlane
{
	GLfloat x,y,z;
    GLfloat u, v;
};

class Plane{
public:
    // Constructor that takes the number of subdivisions for the plane
    Plane();

    // Destructor
    ~Plane();

    void init(wolf::Program* shader, Camera* camera);
    void render();
    void setScale(glm::vec3);
    void setPosition(glm::vec3);
    void setShader(wolf::Program* shader);
private:
    wolf::VertexBuffer* m_VBplane = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    
    wolf::Program* m_pProgram = 0;
    Camera* m_camera = nullptr;
    wolf::Texture* m_texture;

    glm::vec3 m_Scale;
    glm::mat4 m_World = glm::mat4(1.0f);

    
    void generateVertices();
    void setCamera(Camera* camera);

    std::vector<VertexPlane> vertices;
    

};