#include "../HeaderFiles/Import.h"         // Contains all necessary imports for OpenGL

//_________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________

//-_-_-_-_-_-_-_Camera/View Attributes_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
int azimuth = 0;                            // angle to x-axis
int elevation = 0;                          // angle (up) to z-axis
double zoom = 3;                            // dimension/zoom, distance from origin
unsigned short int view_mode = 0;           // 0 - orthogonal, 1 - perspective, 2 = first person
bool toggle_axes = true;
double aspect_ratio = 1;                    // aspect ratio
int field_of_view = 55;                     // field of view
int developer_mode = 1;                     // controls differ if in developer mode --> set this to zero on release
int display_parameters = 0;                 // when pressed, current relevant parameters will be printed to console

//-_-_-_-_-_-_-_Light Attributes_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
int sun_on = 1;                             // turn lighting on/off
bool sun_paused = 0;                        // stop/start sun movement
double curr_time = 0;
bool time_flag = false;                     // used to stop/start sun from same position if paused
double sub_time = 0;                        // used to stop/start sun from same position if paused
double prev_time = 0;                       // used to stop/start sun from same position if paused
//int sun_move = 1;                           // start with Idle function --> sun moving
float sun_distance = 2.0f;                  // distance of sun from origin
int sun_increment = 10;                     
int sun_emission = 0;                       // Emission intensity (%)   ...purpleish, night vibe
int sun_ambient = 10;                       // Ambient intensity (%)    
int sun_diffuse = 50;                       // Diffuse intensity (%)
int sun_specular = 0;                       // Specular intensity (%)   ...yellowish, day vibe
int sun_shininess = 0;                      // Shininess (power of two)
float sun_shiny = 1;                        // Shininess (value)
float sun_azimuth = 90.0f;                  // Light azimuth
float sun_elevation = 0.0f;                 // Elevation of light
int smooth = 1;                             // toggles smooth or flat shading

//-_-_-_-_-_-_-_Mesh Attributes_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
const float start_x = -1;
const float start_y = -1;
const float stretch_x = 2;
const float stretch_y = 2;
const float step_size = 0.01;
const int num_x_vertices = (stretch_x/step_size) + 1;
const int num_y_vertices = (stretch_y/step_size) + 1;
const int dimensions = 3;
const int mesh_positions_length = num_x_vertices*num_y_vertices*dimensions;             // dimension of each vertice
float mesh_positions[mesh_positions_length];                                            // vertices store positions of triangle mesh
const int num_triangles = (num_x_vertices-1)*(num_y_vertices-1)*2;
//const int mesh_indices_length = num_triangles*3;                                      // 3 indices for each triangle
//float mesh_indices[mesh_indices_length];                                              // stores indices of 
const int mesh_normals_length = num_triangles*3;                                        // x, y, z for each triangle normal --> storing only 1 normal per triangle for low-poly terrain
float mesh_normals[mesh_normals_length];                                                // 3d normals of each triangle

//-_-_-_-_-_-_-_Heightmap Attributes_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
const char* austrailia_heightmap = "Resources/Images/austrailia_heightmap.png";
const char* ireland_heightmap = "Resources/Images/ireland_heightmap.png";
const char* island_heightmap = "Resources/Images/island_heightmap.png";
const char* middleeast_heightmap = "Resources/Images/middleeast_heightmap.png";
const char* mountains_heightmap = "Resources/Images/mountains_heightmap.png";
const char* sealine_heightmap = "Resources/Images/sealine_heightmap.png";
vector<float> austrailia_zvals;
vector<float> ireland_zvals;
vector<float> island_zvals;
vector<float> middleeast_zvals;
vector<float> mountains_zvals;
vector<float> sealine_zvals;
vector<vector<float>> maps;         // vector of vectors containing all map data
float z_vals_max;
int maps_index = 0;

//_________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________

void PrintData(float data[], int data_length){
    for(int i = 0; i < data_length; i++){
        if((i+1)%3 == 0){                   //end line on 3rd vertex (z)
            cout << data[i] << endl;
        }
        else{
            cout << data[i] << "   ";
        }
    }
}

void GenMeshNormals(){
    // Data now stored and ready, Render two different colored triangles for each square
    int index = 0;
    for(int row = 0; row < (num_y_vertices - 1); row++){                // iterate through rows of y
        int top_left_index = num_x_vertices * dimensions * (row+1);           //init top left/right starting indice
        int top_right_index = top_left_index + dimensions;
        
        for(int col = 0; col < (num_x_vertices -1); col++){     // for each row, iterate through columns of x
            int curr = (col*dimensions) + (row*num_x_vertices*dimensions);
            
            // Bottom triangle vertices
            vec3 t1_v1(mesh_positions[curr], mesh_positions[curr+1], mesh_positions[curr+2]);
            vec3 t1_v2(mesh_positions[curr+3], mesh_positions[curr+4], mesh_positions[curr+5]);
            vec3 t1_v3(mesh_positions[top_right_index],  mesh_positions[top_right_index+1],  mesh_positions[top_right_index+2]);
            vec3 t1_normal = cross((t1_v3 - t1_v2), (t1_v1 - t1_v2));
            t1_normal = normalize(t1_normal);
            //cout << "t1_normal: " << "x: " << t1_normal[0] << " y: " << t1_normal[1] << " z: " << t1_normal[2] << endl;
            mesh_normals[index] = t1_normal[0];
            index++;
            mesh_normals[index] = t1_normal[1];
            index++;
            mesh_normals[index] = t1_normal[2];
            index++;

            // Top triangle vertices
            vec3 t2_v1(mesh_positions[top_right_index],  mesh_positions[top_right_index+1],  mesh_positions[top_right_index+2]);
            vec3 t2_v2(mesh_positions[top_left_index],  mesh_positions[top_left_index+1],  mesh_positions[top_left_index+2]);
            vec3 t2_v3(mesh_positions[curr],  mesh_positions[curr+1],  mesh_positions[curr+2]);
            vec3 t2_normal = cross((t2_v3 - t2_v2), (t2_v1 - t2_v2));
            t2_normal = normalize(t2_normal);
            //cout << "t2_normal: " << "x: " << t2_normal[0] << " y: " << t2_normal[1] << " z: " << t2_normal[2] << endl;
            mesh_normals[index] = t2_normal[0];
            index++;
            mesh_normals[index] = t2_normal[1];
            index++;
            mesh_normals[index] = t2_normal[2];
            index++;

            top_left_index +=3;
            top_right_index +=3;
        }
    }
}

void RenderMesh(){
    // Data now stored and ready, Render two different colored triangles for each square
    int normal_index = 0;
    for(int row = 0; row < (num_y_vertices - 1); row++){                // iterate through rows of y
        int top_left_index = num_x_vertices * dimensions * (row+1);           //init top left/right starting indice
        int top_right_index = top_left_index + dimensions;
        for(int col = 0; col < (num_x_vertices -1); col++){     // for each row, iterate through columns of x
            int curr = (col*dimensions) + (row*num_x_vertices*dimensions);
            //cout << "curr: " << curr << endl;
            // Bottom triangle
            glNormal3f(mesh_normals[0], mesh_normals[1], mesh_normals[2]);               // per face/primitive normal for now, smoother image may be developed with normal per vertex... (TODO)
            glBegin(GL_TRIANGLES);
            if(!mesh_positions[curr+2]){
                glColor3f(0, 0, 0.502);             // zero values are set to blue (water/ocean)
            }
            else{
                glColor3f(0, mesh_positions[curr+2]/z_vals_max, 0);                 // green depth depends on z-value: green = f(z) = z/z_values_max
            }
            glVertex3f(mesh_positions[curr],  mesh_positions[curr+1],  mesh_positions[curr+2]);
            glVertex3f(mesh_positions[curr+3],  mesh_positions[curr+4],  mesh_positions[curr+5]);
            glVertex3f(mesh_positions[top_right_index],  mesh_positions[top_right_index+1],  mesh_positions[top_right_index+2]);
            glEnd();

            // Top triangle
            glNormal3f(mesh_normals[3], mesh_normals[4], mesh_normals[5]);
            glBegin(GL_TRIANGLES);
            if(!mesh_positions[curr+2]){
                glColor3f(0, 0, 0.502);             // zero values are set to blue (water/ocean)
            }
            else{
                glColor3f(0, mesh_positions[curr+2]/z_vals_max, 0);                 // green depth depends on z-value: green = f(z) = z/z_values_max
            }
            glVertex3f(mesh_positions[top_right_index],  mesh_positions[top_right_index+1],  mesh_positions[top_right_index+2]);
            glVertex3f(mesh_positions[top_left_index],  mesh_positions[top_left_index+1],  mesh_positions[top_left_index+2]);
            glVertex3f(mesh_positions[curr],  mesh_positions[curr+1],  mesh_positions[curr+2]);
            glEnd();

            normal_index += 6;
            top_left_index +=3;
            top_right_index +=3;
        }
    }
}

vector<float> ProcessHeightmap(const char* img_path){
    // Load Heightmap
    int width, height, nChannels;
    unsigned char *data = stbi_load(img_path, &width, &height, &nChannels, 0);
    //cout << "Width: " << width << "   Height: " << height << "   nChannels: " << nChannels << endl;
    
    // Generate Vertices based on color
    vector<float> z_vals;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            unsigned char* texel = data + (x + width * y) * nChannels;      // retrieve texel for (x, y) tex coord
            unsigned char z = texel[0];                                     // raw height at coordinate
            z_vals.push_back(z);                              // z vertex
        }
    }

    // Scale based on max/min, shift down by -0.5
    float max = *max_element(z_vals.begin(), z_vals.end());
    //float min = *min_element(z_vals.begin(), z_vals.end());
    float z_scale = 0.15/(max);
    float z_shift = 0.0f;
    for(unsigned int z = 0; z < z_vals.size(); z++){
        //float scale = 1.0/(z_vals[z]/2.0);
        z_vals[z] = z_vals[z] * z_scale - z_shift;
    }

    stbi_image_free(data);  // free heightmap from memory
    return z_vals;          // return z values
}

void GenMeshVertices(vector<float> z_vals){
    //int indices[];
    //int temp_square_length = *(&temp_square + 1) - temp_square;
    //PrintVertices(temp_square, temp_square_length);

    // Going row by row, store vertices at intervals specified by step_size
    int index = 0;
    int z_index = 0;
    float x = start_x;
    float y = start_y;

    for(int j = 0; j < num_y_vertices; j++){
        //cout << "" << endl;
        //cout << "j: " << j << endl;
        for(int i = 0; i < num_x_vertices; i++){
            //cout << "i: " << i << "  ";
            mesh_positions[index] = x + i*step_size;        //x
            index++;
            mesh_positions[index] = y + j*step_size;        //y
            index++;
            //mesh_positions[index] = sin(10*mesh_positions[index-2] + 3.14/2.0)/5;      //z is a sin wave for shader testing
            mesh_positions[index] = z_vals[z_index];        //z
            index++;
            z_index++;
        }
    } 
}

static void RenderSun(double tx, double ty, double tz, double r){
    glDisable(GL_LIGHTING);
    //Render sun as GLUT object so that it is not effected by lighting
    glPushMatrix();                 // Save transformation
    glTranslated(tx,ty,tz);
    glScaled(r,r,r);                // Offset, scale and rotate
    glColor3f(1,1,0.3);             // Yellow ball
    glutSolidSphere(1.0,16,16);
    glPopMatrix();                  // Undo transofrmations
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);       // Erase the window and the depth buffer
    glEnable(GL_DEPTH_TEST);                                // Enable Z-buffering in OpenGL
    glLoadIdentity();                                       // Undo previous transformations

    // Set View mode based on selection: 0 - Orthogonal, 1 - Perspective, 2 - First Person
    if (view_mode == 0){
        // Orthogonal View
        glRotatef(elevation,    1, 0, 0);
        glRotatef(azimuth,      0, 0, 1);                       //(degrees of rotation, axis)       //glRotatef(azimuth,      0, 1, 0);
    }
    else if (view_mode == 1){
        // Perspective View
        double Ex = -2*zoom*Sin(azimuth)*Cos(elevation);
        double Ey = +2*zoom*Cos(azimuth)*Cos(elevation);
        double Ez = +2*zoom*Sin(elevation);
        // double Ex = -2*zoom*Sin(azimuth)*Cos(elevation);
        // double Ey = +2*zoom*Sin(elevation);
        // double Ez = +2*zoom*Cos(azimuth)*Cos(elevation);
        gluLookAt(Ex,Ey,Ez, 0,0,0, 0,0,Cos(elevation));         //(eye x, y, z, center x, y, z, up x, y, z)
    }
    else{   
        // First Person View
        // TODO
    }

    glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

    // Set lighting - main light source is the 'Sun'
    if(sun_on){
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01f*(float)sun_ambient,0.01f*(float)sun_ambient,0.01f*(float)sun_ambient,1.0};
        float Diffuse[]   = {0.01f*(float)sun_diffuse,0.01f*(float)sun_diffuse,0.01f*(float)sun_diffuse,1.0};
        float Specular[]  = {0.01f*(float)sun_specular,0.01f*(float)sun_specular,0.01f*(float)sun_specular,1.0};
        float Position[]  = {sun_distance*Cos(sun_azimuth),sun_elevation,sun_distance*Sin(sun_azimuth),1.0};    //  Light position
        //  Draw light position as ball (still no lighting here)
        RenderSun(Position[0], Position[1], Position[2] , 0.1);
        glEnable(GL_NORMALIZE);                                         //  OpenGL should normalize normal vectors, may not be necessary
        //  Enable lighting
        glEnable(GL_LIGHTING);
        int local = 0;                                                  //local viewer model can be set to one if feature necessary
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);               //  Location of viewer for specular calculations
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);      //  glColor sets ambient and diffuse color materials
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHT0);                                            //  Enable light 0
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
    }
    else{
        glDisable(GL_LIGHTING);
    }
    
    // Draw Calls Here
    //++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++
    RenderMesh();

    //++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++

    // Draw Axes
    if(toggle_axes){
        // Draw Lines
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(1.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 1.0, 0.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 1.0);        // 1.0 specifies the length of the lines
        glEnd();
        // Label axes
        glRasterPos3d(1.1, 0.0, 0.0);
        Print("X");
        glRasterPos3d(0.0, 1.1, 0.0);
        Print("Y");
        glRasterPos3d(0.0, 0.0, 1.1);
        Print("Z");
    }

    // If developer mode on, print important attributes
    if(developer_mode){
        //Onscreen Prints
        #ifdef USEGLEW
            glColor3f(1, 1, 1);
            glWindowPos2i(5, 5);            // Depends on GLEW!!!
            Print("Developer Mode");
        #endif

        if(display_parameters){
            // Terminal Prints
            cout << "_______________________________________________" << endl;
            cout << "azimuth: " << azimuth << endl;     //  Display parameters
            cout << "elevation: " << elevation << endl;
            cout << "zoom: " << zoom << endl;
            cout << "field_of_view: " << field_of_view << endl;
            if(view_mode == 0){
                cout << "view_mode: orthogonal" << endl;
            }
            else if(view_mode == 1){
                cout << "view_mode: perspective" << endl;
            }
            else{
                cout << "view_mode: first person" << endl;
            }
            // Lighting parameters
            if(sun_on){
                cout << "sun_azimuth: " << sun_azimuth << endl;
                cout << "sun_elevation: " << sun_elevation << endl;
                cout << "sun_ambient: " << sun_ambient << endl;
                cout << "sun_diffuse: " << sun_diffuse << endl;
                cout << "sun_specular: " << sun_specular << endl;
                cout << "sun_emission: " << sun_emission << endl;
            }
            display_parameters = 0;     //reset so it is only displayed once
        }
    }

    //ErrCheck("Display");
    glFlush();                          // empty buffers and execute rendering, call before user input???
    glutSwapBuffers();                  // swaps the buffers of current window (if double buffered --> yes)
}

void Reshape(int width, int height){
    aspect_ratio = ( height > 0) ? (double)width / height : 1;          //  Ratio of the width to the height of the window
    glViewport(0, 0, RES*width, RES*height);                            //  Set the viewport to the entire window
    if(view_mode == 2){
        // First Person - TODO
    }
    Project(view_mode ? field_of_view : 0, aspect_ratio, zoom);         //  Set projection
}

void Idle(){
    if(sun_paused && !time_flag){
        prev_time = curr_time-sub_time;        // gets time in seconds
        // no change to sun_azimuth
        time_flag = true;
        //cout << "Sun paused, prev_time: " << prev_time << endl;
    }
    else if(!sun_paused){
        if(time_flag){
            
            sub_time = glutGet(GLUT_ELAPSED_TIME)/1000.0 - prev_time;
            time_flag = false;
            //cout << "starting again, sub_time: " << sub_time << "   prev_time: " << prev_time << endl;
        }
        curr_time = glutGet(GLUT_ELAPSED_TIME)/1000.0;
        //cout << "curr_time: " << curr_time << "    curr_time-sub_time: " << curr_time-sub_time << endl;
        sun_azimuth = fmod(20*(curr_time-sub_time), 360.0);                     // multiple is how many degrees rotating per second
        glutPostRedisplay();                // indicates current window needs redisplaying (change has occured)
    }
    // Where time should be tracked
    
    //cout << time << endl;
    
}

void SwitchMap(){
    if(maps_index == (int)maps.size()-1){
        maps_index = 0;
    }
    else{
        maps_index++;
    }
    // Generate Mesh Vertices as specified in globals
    GenMeshVertices(maps[maps_index]);      //maps_index specifies initial map (0)
    GenMeshNormals();
    z_vals_max = *max_element(maps[maps_index].begin(), maps[maps_index].end());   //get max value for current map (for gradient coloring)
}

void SpecialBindings(int key, int x, int y){
    //Shared keybindings (player and developer mode)
    if      (key == GLUT_KEY_F1)                { developer_mode = 1 - developer_mode; }    //  F1 - Toggle developer mode
    
    // Developer Mode Keybindings
    if(developer_mode){
        if      (key == GLUT_KEY_F2)                { view_mode = 1 - view_mode; }              //  F2 - Change View Mode
        else if (key == GLUT_KEY_F3)                { sun_paused = 1 - sun_paused; }                //  F3 - Pause motion of sun
        else if (key == GLUT_KEY_F4)                { toggle_axes = 1 - toggle_axes; }          //  F4 - Toggle Axes
        else if (key == GLUT_KEY_F5)                { display_parameters = 1; }                 //  F5 - Display parameters once
        else if (key == GLUT_KEY_F6)                { SwitchMap(); }                            //  F6 - Switch Map
        else if (key == GLUT_KEY_F7)                { sun_on = 1 - sun_on; }                    //  F7 - Turn sun (light) on/off
        else if (key == GLUT_KEY_RIGHT)             { azimuth += 5; }                           //  Right arrow key - increase angle by 5 degrees
        else if (key == GLUT_KEY_LEFT)              { azimuth -= 5; }                           //  Left arrow key - decrease angle by 5 degrees
        else if (key == GLUT_KEY_UP)                { elevation += 5; }                         //  Up arrow key - increase elevation by 5 degrees
        else if (key == GLUT_KEY_DOWN)              { elevation -= 5; }                         //  Down arrow key - decrease elevation by 5 degrees
        else if (key == GLUT_KEY_PAGE_DOWN)         { zoom += 0.1; }                            //  PageUp key - increase dim
        else if (key == GLUT_KEY_PAGE_UP && zoom>1) { zoom -= 0.1; }                            //  PageDown key - decrease dim
    }
    // Player Mode Keybindings
    else{
        //TODO: Player controls
        cout << "";
    }

    azimuth %= 360;
    elevation %= 360;               //  Keep angles to +/-360 degrees
    Project(view_mode ? field_of_view : 0, aspect_ratio, zoom);     //  Update projection
    //glutIdleFunc(sun_paused ? Idle : NULL);                           //  Animate if requested
    glutPostRedisplay();                                            //  Tell GLUT it is necessary to redisplay the scene
}

void KeyboardBindings(unsigned char key, int x, int y){
    //Shared keybindings (player and developer mode)
    if (key == 27){                                                 //  Exit on ESC
        PrintData(mesh_normals, mesh_normals_length);
        exit(0);
    }
    
    // Developer Mode Keybindings
    if(developer_mode){                                             // if developer mode on
        // Lighting Adjustments
        if      (key=='a' && sun_ambient>0){    sun_ambient -= 5; }         // Ambient level
        else if (key=='A' && sun_ambient<100){  sun_ambient += 5; }  
        else if (key=='d' && sun_diffuse>0){    sun_diffuse -= 5; }         // Diffuse level
        else if (key=='D' && sun_diffuse<100){  sun_diffuse += 5; }
        else if (key=='s' && sun_specular>0){   sun_specular -= 5; }        // Specular level
        else if (key=='S' && sun_specular<100){ sun_specular += 5; }
        else if (key=='e' && sun_emission>0){   sun_emission -= 5; }        // Emission level 
        else if (key=='E' && sun_emission<100){ sun_emission += 5; }
        // View Controls
        else if (key == '-' && key>1){          field_of_view++; }
        else if (key == '=' && key<179){        field_of_view--; }
    }

    // Player Mode Keybindings
    else{                                                           // developer mode off, player mode
        //TODO: Player controls
        cout << "";
    }
    
    //  Reproject
    Project(view_mode ? field_of_view : 0, aspect_ratio, zoom);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

void Fatal(const char* error_message){
   cout << error_message << endl;
   exit(0);
}

void Init(){
    if(developer_mode){
        view_mode = 1;
        azimuth = 45;
        elevation = 35;
        zoom = 1.6;
    }

    // Preprocess all maps for easy switching & add them to maps vector
    ireland_zvals = ProcessHeightmap(ireland_heightmap);        
    maps.push_back(ireland_zvals);   
    austrailia_zvals = ProcessHeightmap(austrailia_heightmap);
    maps.push_back(austrailia_zvals);                                   // add vector to maps                  
    island_zvals = ProcessHeightmap(island_heightmap);
    maps.push_back(island_zvals);                                 
    middleeast_zvals = ProcessHeightmap(middleeast_heightmap);          // may not be feasible heightmap
    maps.push_back(middleeast_zvals);                                  
    mountains_zvals = ProcessHeightmap(mountains_heightmap);
    maps.push_back(mountains_zvals);                                  
    sealine_zvals = ProcessHeightmap(sealine_heightmap);
    maps.push_back(sealine_zvals);                                   

    z_vals_max = *max_element(maps[maps_index].begin(), maps[maps_index].end());    //set max value for initial map
    // Generate Mesh Vertices as specified in globals
    GenMeshVertices(maps[maps_index]);      //maps_index specifies initial map (0)
    GenMeshNormals();

    // Set null arguments and initialize GLUT
    int arg_c = 0;
    char* arg_v[1] = {(char*)"Nothing"};
    glutInit(&arg_c, arg_v);                                        // initialize GLUT
}

//_________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________

int main() {
    Init();         // initialize

    // Display Window
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);       // (true color | z buffering | double buffered)
        // Double buffering allows concurrent drawing on one buffer and display on another
    glutInitWindowSize(600,600);                                    // size window 
    glutCreateWindow("Game");                                       // name window

    #ifdef USEGLEW
        if(glewInit() != GLEW_OK) Fatal("ERROR: Failed to Initialize GLEW");
    #endif
    //if(glewInit() != GLEW_OK) Fatal("ERROR: Failed to Initialize GLEW");

    // Set Callbacks (main game loop)
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutSpecialFunc(SpecialBindings);
    glutKeyboardFunc(KeyboardBindings);
    glutIdleFunc(Idle);

    //ErrCheck("main");
    glutMainLoop();

    
	return 0;
}