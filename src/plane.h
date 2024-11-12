#pragma once
#include <vector>
#include "../wolf/wolf.h"


struct Vertex
{
	GLfloat x,y,z;

};

class Plane{
public:
    // Constructor that takes the number of subdivisions for the plane
    Plane(int subdivisions) : subdivisions(subdivisions) {}

    // Destructor
    ~Plane();

    void init() ;
    void update(float dt) ;
    void render(glm::mat4& view, glm::mat4& projection);
    void setShader(wolf::Program*);


private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;

    int subdivisions;
    void generateVertices();
    std::vector<Vertex> vertices;
    float m_time;

};

