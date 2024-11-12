#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"

class CityScape: public wolf::App
{
public:
    CityScape() : wolf::App("CityScape")
    {
    }

    ~CityScape()
    {
    }

    void update(float dt) override
    {
        
    }

    void render() override
    {
        
    }

};

int main(int, char**) {
    CityScape cityScape;
    cityScape.run();
}