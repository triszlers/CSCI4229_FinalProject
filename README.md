## Instructions
Compilation:
    > g++ -Wall -o Game SourceFiles/Game.cpp -lfreeglut -lglew32 -lglu32 -lopengl32 -lm
Running:
    > ./Game

## Development Plans
* Generate mesh on XY plane, test mesh functions with simple Glut triangle rendering
* Update: Continue using GLUT objects to draw
    * Get normals for every triangle in mesh--> TEST normals with lighting
* Get lighting effects working (a slow moving sun on a timer)

## Description
* Import errors and varied use of global variables in main function hindered formal abstraction of functions... result is a large file application
* Mesh vertices are generated/stored on the xy plane for each x value in a row, then for each x in the next y value
    * see Resources/Images/mesh_data_layout.png

## Credit/Reuse
* Many functions/structure/shaders from CSCI4229 (Fall 2023) library, professor Willem A. (Vlakkies) Schreuder
* Terrain generation inspirations:
    * Youtube: Thin Matrix - https://www.youtube.com/watch?v=l6PEfzQVpvM, OGLDEV - https://www.youtube.com/watch?v=xoqESu9iOUE, The Cherno (OpenGL series)
    * Blog: Iago Toral - https://blogs.igalia.com/itoral/2016/10/13/opengl-terrain-renderer-rendering-the-terrain-mesh/
* Heightmap Processing
    * Function based on learnopengl.com example - https://learnopengl.com/Guest-Articles/2021/Tessellation/Height-map
    * stb_image library - https://github.com/nothings/stb/blob/master/stb_image.h