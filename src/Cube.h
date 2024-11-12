#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../wolf/wolf.h"

class Cube {
public:
    Cube();
    ~Cube();

    void render(glm::mat4& view, glm::mat4& projection);
    void init();

private:
    wolf::VertexBuffer* m_pVB = 0;    
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;

};
