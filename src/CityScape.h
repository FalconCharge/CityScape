#pragma once
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "camera.h"
#include "plane.h"
#include "grid.h"
#include "road.h"
#include "../samplefw/Grid3D.h"


//Generates the city enviroment
class CityScape : public wolf::App {
public:
    CityScape();
    ~CityScape();

    void init();
    void update(float dt) override;
    void render() override;

    void regenerate();
    

private:
    Camera* camera;
    Grid3D* grid3d;
    Road* road;
    
    
    wolf::Program* m_plane = 0;
    wolf::Program* m_building = 0;
    wolf::Program* m_buildingRoof = 0;
    wolf::Program* m_default = 0;

    std::vector<Grid*> grids;

    Plane* plane1;
    void createGrid();
};
