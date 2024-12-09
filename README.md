#OverView of CityScape
CityScape is an OpenGL-based city simulation project that creates a procedurally generated city. 
The user is able control a camera to navigate through the city, through a first-person perspective. 
The project features random city generation with buildings, roadways, and a dynamic camera system. 
The primary purpose of this project is to learn openGl.

Camera Movement Controls

    Use the WASD keys for horizontal movement and Q/E for vertical movement.

        W: Move forward along the camera's facing direction.
        S: Move backward along the camera's facing direction.
        A: Strafe left (move left relative to the camera's facing direction).
        D: Strafe right (move right relative to the camera's facing direction).
        Q: Move downward (negative Y axis).
        E: Move upward (positive Y axis)

        left Shift: Sprint (ispeedboost when held down)
        I: Invert (Inverts the camera's mouse movement)

        Sens is hardcoded into the code 

City Generation

CityScape features procedural generation, which means that the buildings and the city layout are randomly created each time the project is run.

City Features:

    Buildings: Vary in size and height, placed randomly within the city grid.
    Roadways: Generated between grids going in one direction
    Plane: The ground
    Grid Layout: The city is divided into a grid system, with each section containing buildings of varying sizes.
    lighting: There is lighting added into the city with a day/night cycle

Wolf changes:

I have made a few small changed to wolf such as:
    W_App.cpp
    W_App.h
    I added a setMousePos function
    I added a hideCursor function

optimizatoins

small optimizations were made.
Started at 35FPS
Currently got it to 40FPS