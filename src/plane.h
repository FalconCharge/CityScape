#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"

struct Vertex
{
	GLfloat x,y,z;
    //GLfloat u,v;
};

class Plane{
public:
    // Constructor that takes the number of subdivisions for the plane
    Plane(int subdivisions) : subdivisions(subdivisions) {}

    // Destructor
    ~Plane();

    void init(wolf::Program* m_program);
    void update(float dt) ;
    void render();
    void setCamera(Camera* camera);
    void loadTexture(char* texturePath);


private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    Camera* m_camera = nullptr; // Pointer to the camera
    GLuint m_tex = 0;

    int subdivisions;
    void generateVertices();
    std::vector<Vertex> vertices;
    float m_time;

};