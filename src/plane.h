#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include <vector>
#include "../samplefw/OrbitCamera.h"

struct Vertex
{
	GLfloat x,y,z;
	//GLubyte r,g,b,a;
};

class Plane: public Sample {
public:
    // Constructor that takes the number of subdivisions for the plane
    Plane(wolf::App* pApp, int subdivisions) : Sample(pApp,"Plane"), subdivisions(subdivisions) {}

    // Destructor
    ~Plane();

    void init() override;
    void update(float dt) override;
    void render(int height, int width) override;
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

