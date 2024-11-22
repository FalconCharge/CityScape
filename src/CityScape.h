#pragma once
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "camera.h"
#include "plane.h"
#include "grid.h"
#include "fakeGrid.h"
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
    Grid* grid1;
    FakeGrid* fakeGrid;

    Grid3D* grid3d;
    
    
    wolf::Program* m_plane = 0;
    wolf::Program* m_building = 0;

    std::vector<Grid*> grids;

    Plane* plane1;
    void createGrid();
    void createFakeGrid();
};
