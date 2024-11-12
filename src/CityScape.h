#pragma once
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "camera.h"
#include "plane.h"


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
    wolf::Program* m_plane = 0;

    Plane* plane1;
};
