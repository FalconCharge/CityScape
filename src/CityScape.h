#pragma once
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "camera.h"
#include "plane.h"
#include "grid.h"
#include "road.h"
#include "sun.h"
#include "../samplefw/Grid3D.h"


//Generates the city enviroment
class CityScape : public wolf::App {
public:
    CityScape();
    ~CityScape();

    void init();
    void update(float dt) override;
    void render() override;

    void regenerate();  //Regenerates a new city
    

private:
    Camera* camera;
    Sun* sun;
    Grid3D* grid3d;
    
    wolf::Program* m_plane = 0;         //Shader for the plane (ground)
    wolf::Program* m_building = 0;      //Shader for the walls of the building
    wolf::Program* m_buildingRoof = 0;  //Shader for the roof of the building
    wolf::Program* m_road = 0;
    wolf::Program* m_default = 0;       //A default shader 

    std::vector<Grid*> grids;           //Storage for all the grids
    std::vector<Road*> roads;           //storage for the roads
    std::vector<Plane*> planes;          //storage for the planes

    void createGrid();

};
