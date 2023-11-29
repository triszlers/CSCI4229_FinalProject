## Instructions
* LAUNCH THE EXECUTABLE "Game.exe"
* Compiling/Running:
    * Compilation: > g++ -Wall -o Game SourceFiles/Game.cpp -lfreeglut -lglew32 -lglu32 -lopengl32 -lm
    * Running: > ./Game
* Controls:
    * Shared Controls (developer and player)
        * F1 - Toggle Developer Mode:
    * Developer Mode Controls:
        * F2 - Change view (orthogonal/perspective)
        * F3 - Pause the sun (primary light source)
        * F4 - Toggle Axes
        * F5 - Display Parameters in terminal
        * F6 - Switch Map
        * F7 - Turn sun (light) on/off
        * Arrow Keys: Rotate around origin
        * Page up/down: Zoom in/out
        * A/a: Increase/decrease ambient light
        * D/d: Increase/decrease diffuse light
        * S/s: Increase/decrease specular level
        * E/e: Increase/decrease emission level
        * =/-: Increase/decrease field of view
    * Player Controls:
        * TODO

## Development Plans
* Color Mountaintops 
* Give different maps different 'uniforms' based on the environment there
* Store max values in maps array for preprocessing speed, along with a 'multiplier' which specifies a specific max height multiple for that map
* Set up mesh step size so that differently sized square images can be processed and rendered

## Description/Notes
* Abstraction hindered by some odd circular include errors... result is a large single file application
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