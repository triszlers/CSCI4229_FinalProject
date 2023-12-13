## Instructions
* LAUNCH THE EXECUTABLE "final.exe" IF ON WINDOWS
* Compiling/Running:
    * Compilation:      > make
    * Running:          > ./final
    * Clean:            > make clean

* Controls:
    * Player Controls:
        * F1 - Toggle Developer Mode (not recommended)
        * F2 - Pause the Sun
        * F3 - Change Map
        * Arrow Keys - Change View
        * A/a - Turn 90deg Left
        * D/d - Turn 90deg Right

    * Developer Mode Controls:
        * F1 - Toggle Developer Mode
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

## Description/Notes
* This game allows you to navigate a scene in a yellow aircraft inspired by the Piper cub. Fly/look around with the specified controls and change map as desired. I had hoped to add more visual detail/variance before the project deadline, but getting general motion and heightmap generation to work as desired was quite a difficult task. Thank you for viewing my project. 

## Development Notes
* Abstraction hindered by some odd circular include errors... result is a large single file application
* Mesh vertices are generated/stored on the xy plane for each x value in a row, then for each subsequent y column
    * see Resources/Images/mesh_data_layout.png
* Dependencies/ contains unused include files for possible independent linking in the future

## Credit/Reuse
* Many functions/structure/shaders from CSCI4229 (Fall 2023) library, professor Willem A. (Vlakkies) Schreuder, including...
    * Cylinder function
    * Fatal function and all supporting functions in Import.h
    * Reshape function
    * The general layout and orginazational method of code is directly inspired by CSCI4229 examples. 
* Terrain generation:
    * Ideation 
        * Youtube: Thin Matrix - https://www.youtube.com/watch?v=l6PEfzQVpvM, OGLDEV - https://www.youtube.com/watch?v=xoqESu9iOUE, The Cherno (OpenGL series)
        * Blog: Iago Toral - https://blogs.igalia.com/itoral/2016/10/13/opengl-terrain-renderer-rendering-the-terrain-mesh/
    * Heightmap Processing
        * Function to process heightmaps based on learnopengl.com example - https://learnopengl.com/Guest-Articles/2021/Tessellation/Height-map
        * stb_image library - https://github.com/nothings/stb/blob/master/stb_image.h