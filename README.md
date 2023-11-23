## Instructions
Compilation:
    > g++ -Wall -o Game SourceFiles/Game.cpp -lfreeglut -lglew32 -lglu32 -lopengl32 -lm
Running:
    > ./Game

## Development Plans
* Generate mesh on XY plane, test mesh functions with simple Glut triangle rendering
* Once vertices are generated properly, draw properly w/ buffers/indices/simple shader
* Examine methods of efficiency drawing, make the vertex data constant for specific object drawing (houses, roads, etc).
    * Expand vertice dimensions for texture/normal caculation
* Get lighting effects working (a slow moving sun)