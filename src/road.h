#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"
#include "camera.h"
#include <iostream>

struct VertexRoad
{
	GLfloat x,y,z;
    GLfloat u,v;
};

class Road {
public:
    // Constructor: Takes the road's length in X and Z and its starting position
    Road(float lengthX, float lengthZ, const glm::vec3& startPosition);

    // Destructor
    ~Road();

    // Getters for road properties
    float getLengthX() const;
    float getLengthZ() const;
    glm::vec3 getStartPosition() const;

    // Setters for road properties (if modification is needed)
    void setLengthX(float lengthX);
    void setLengthZ(float lengthZ);
    void setStartPosition(const glm::vec3& startPosition);
    void setCamera(Camera* m_camera);
    void setShader(wolf::Program* shader);

    // Render method to draw the road
    void render();
    void init();

private:
    void setupBuffers();



    Camera* m_camera;
    wolf::Program* m_program = 0;
    wolf::VertexBuffer* m_pVB = 0;
    wolf::IndexBuffer* m_pIB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Texture* m_texture;

    std::vector<VertexRoad> vertices;
    std::vector<unsigned int> indices;

    // Length of the road in the X and Z directions
    float m_lengthX;
    float m_lengthZ;

    glm::mat4 modelMatrix;

    // Starting position of the road
    glm::vec3 m_startPosition;

};