#pragma once
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "camera.h"
#include "plane.h"
#include "grid.h"


//Generates the city enviroment
class CityScape : public wolf::App {
public:
    CityScape();
    ~CityScape();

    void init();
    void update(float dt) override;
    void render() override;
    

private:
    Camera* camera;
    Grid* grid;
    wolf::Program* m_plane = 0;
    wolf::Program* m_building = 0;

    Plane* plane1;
};
