#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"
#include "sun.h"
#include <iostream>

struct VertexBuilding
{
	GLfloat x,y,z;       //Pos
    GLfloat u,v;         //Tex coords
    GLfloat nx, ny, nz;  // Normal vector
};

class Building {
public:
    ~Building();

    void render();
    void init(wolf::Program* shader, wolf::Program* shaderRoof, Camera* camera);
    void setCamera(Camera* camera);
    void setShader(wolf::Program* m_program, wolf::Program* roofShader);
    void setColor(glm::vec3 color);
    void setPosition(glm::vec3 pos);
    void setScale(glm::vec3 scale);
    void setSun(Sun* sun);
    glm::vec3 getSize() const;
    glm::vec3 getPosition() const;

    static const std::vector<VertexBuilding>& getVertices(); // Return static vertices
    static const std::vector<unsigned short>& getIndices();  // Return static indices
    
private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::IndexBuffer* m_pIB = 0;
    wolf::IndexBuffer* m_pIBR = 0;

    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    wolf::Program* m_roofShader = 0;
    wolf::Texture* m_texture;
    wolf::Texture* m_rooftexture;
    Camera* m_camera = nullptr;

    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_color;
    glm::mat4 mWorld;
    Sun* buildingSun;
    float uScale;
    float vScale;

    void generateVertices();
    void generateIndices();
    std::vector<VertexBuilding> vertices;
    std::vector<unsigned int> indices;
};
