## Instructions
* LAUNCH THE EXECUTABLE "Game.exe"
* Compiling/Running:
    * Compilation:      > make
    * Running:          > ./Game
    * Clean:            > make clean

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
        * F8 - Switch between smooth/flat shading
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
* Scale out erroneous (super large) z values, fix bug with "ProcessHeightmaps()"
* Finish Implmenting First person view to navigate around scene
* Sit first person view inside previously built airplane/cockpit
* Add a skybox --> use color gradient or texture
* Add clouds/weather, adjust emission lighting towards dawn
* Add buildings/features for visual richness
* Add scaliness to water.. possibly identify water z vals and apply moving sin wave to it. 
* IF TIME PERMITS: Set up shadow mapping, water reflections, etc...

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