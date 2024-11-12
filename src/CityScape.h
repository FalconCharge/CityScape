#pragma once
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "camera.h"
#include "cube.h"
#include "plane.h"

class CityScape : public wolf::App {
public:
    CityScape();
    ~CityScape();

    void init();
    void update(float dt) override;
    void render() override;

private:
    Camera* camera;
    wolf::Program* m_pProgram = 0;
    wolf::Program* m_plane = 0;

    Cube cube1;
    Plane* plane1;
};
