//___Include Statements____________________________________________________________________________________________________
#include "../HeaderFiles/Import.h"         // Contains all necessary imports for OpenGL
//#include "../HeaderFiles/Tools.h"          // Some special helper functions


//___Global Variables______________________________________________________________________________________________________

//-_-_-_-_-_-_-_Camera/View Attributes_-_-_-_-_-_-_-_
int azimuth = 0;                            // angle to x-axis
int elevation = 0;                          // angle (up) to z-axis
double zoom = 3;                            // dimension/zoom, distance from origin
unsigned short int view_mode = 0;           // 0 - orthogonal, 1 - perspective, 2 = first person
bool toggle_axes = true;
double aspect_ratio = 1;                    // aspect ratio
int field_of_view = 55;                     // field of view

//___Functions_____________________________________________________________________________________________________________

// Generates Mesh vertices on the x-y plane at specified starting position
    //TODO: Generate Z vertices algorithmically -- for now they are zero
    //test z vertices w/ simple sin wave  in 1 variable (sin(x))
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

void GenMeshVertices(float start_x, float start_y, float stretch_x, float stretch_y, float step_size){
    int dimensions = 3;         // for now each vertex only tracks (x, y, z)
    int num_x_vertices = (int)((stretch_x/step_size) + 1);
    int num_y_vertices = (int)((stretch_y/step_size) + 1);
    int data_length = num_x_vertices*num_y_vertices;       // num of vertices
    data_length = data_length * dimensions;          // dimension of each vertice
    float data[data_length];
    //int indices[];

    // store 4 points which will be rendered in mesh map as 2 triangles
    float temp_square[12] = {
        start_x,            start_y,            0.0f,
        start_x+step_size,  start_y,            0.0f,
        start_x+step_size,  start_y+step_size,  0.0f,
        start_x,            start_y+step_size,  0.0f
    };
    //int temp_square_length = *(&temp_square + 1) - temp_square;
    //PrintVertices(temp_square, temp_square_length);

    // Going row by row, store vertices at intervals specified by step_size
    int index = 0;
    float x = start_x;
    float y = start_y;
    float z = 0;        //z fixed at zero for now
    for(int j = 0; j < num_y_vertices; j++){
        //cout << "" << endl;
        //cout << "j: " << j << endl;
        for(int i = 0; i < num_x_vertices; i++){
            //cout << "i: " << i << "  ";
            data[index] = x + i*step_size;      //x
            index++;
            data[index] = y + j*step_size;      //y
            index++;
            data[index] = z;      //z
            index++;
        }
    }
    //cout << endl;
    //PrintData(data, data_length);
    int num_squares = (num_x_vertices-1)*(num_y_vertices-1);
    // Data now stored and ready, Render two different colored triangles for each square
    for(int row = 0; row < (num_y_vertices - 1); row++){                // iterate through rows of y
        int top_left_index = num_x_vertices * dimensions * (row+1);           //init top left/right starting indice
        int top_right_index = top_left_index + dimensions;
        for(int col = 0; col < (num_x_vertices -1); col++){     // for each row, iterate through columns of x
            int curr = (col*dimensions) + (row*num_x_vertices*dimensions);
            //cout << "curr: " << curr << endl;
            // Bottom triangle (blue)
            glBegin(GL_TRIANGLES);
            glColor3f(0, 0, 0.5);           //blue
            glVertex3f(data[curr],  data[curr+1],  data[curr+2]);
            glVertex3f(data[curr+3],  data[curr+4],  data[curr+5]);
            glVertex3f(data[top_right_index],  data[top_right_index+1],  data[top_right_index+2]);
            glEnd();

            // Top triangle (red)
            glBegin(GL_TRIANGLES);
            glColor3f(0.5, 0, 0);           //red
            glVertex3f(data[top_right_index],  data[top_right_index+1],  data[top_right_index+2]);
            glVertex3f(data[top_left_index],  data[top_left_index+1],  data[top_left_index+2]);
            glVertex3f(data[curr],  data[curr+1],  data[curr+2]);
            glEnd();

            top_left_index +=3;
            top_right_index +=3;
        }
    }






}




void Display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);       // Erase the window and the depth buffer
    glEnable(GL_DEPTH_TEST);                                // Enable Z-buffering in OpenGL
    glLoadIdentity();                                       // Undo previous transformations

    // Set View mode based on selection: 0 - Orthogonal, 1 - Perspective, 2 - First Person
    if (view_mode == 0){
        // Orthogonal View
        glRotatef(elevation,    1, 0, 0);
        glRotatef(azimuth,      0, 1, 0);                       //(degrees of rotation, axis)
    }
    else if (view_mode == 1){
        // Perspective View
        double Ex = -2*zoom*Sin(azimuth)*Cos(elevation);
        double Ey = +2*zoom*Sin(elevation);
        double Ez = +2*zoom*Cos(azimuth)*Cos(elevation);
        gluLookAt(Ex,Ey,Ez, 0,0,0, 0,Cos(elevation),0);         //(eye x, y, z, center x, y, z, up x, y, z)
    }
    else{   
        // First Person View
        // TODO
    }

    // TODO Shading/Light
    glDisable(GL_LIGHTING);

    // Draw Calls Here
    //++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++
    GenMeshVertices(0, 0, 1, 1, 0.1);

    //++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++

    // Draw Axes
    if(toggle_axes){
        // Draw Lines
        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
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
void SpecialBindings(int key, int x, int y){
    if      (key == GLUT_KEY_RIGHT)             { azimuth += 5; }                       //  Right arrow key - increase angle by 5 degrees
    else if (key == GLUT_KEY_LEFT)              { azimuth -= 5; }                       //  Left arrow key - decrease angle by 5 degrees
    else if (key == GLUT_KEY_UP)                { elevation += 5; }                     //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN)              { elevation -= 5; }                     //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_PAGE_DOWN)         { zoom += 0.1; }                        //  PageUp key - increase dim
    else if (key == GLUT_KEY_PAGE_UP && zoom>1) { zoom -= 0.1; }                        //  PageDown key - decrease dim
    else if (key == GLUT_KEY_F1)                { toggle_axes = 1 - toggle_axes; }      //  F1 - Toggle Axes
    else if (key == GLUT_KEY_F2)                { view_mode = 1 - view_mode; }          //  F2 - Change View Mode

    //  Keep angles to +/-360 degrees
    azimuth %= 360;
    elevation %= 360;
    
    //  Update projection
    Project(view_mode ? field_of_view : 0, aspect_ratio, zoom);
    
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}
void KeyboardBindings(unsigned char key, int x, int y){
    //  Exit on ESC
    if (key == 27)
        exit(0);
    
    //  Change field of view angle
    else if (key == '-' && key>1)
        field_of_view--;
    else if (key == '=' && key<179)
        field_of_view++;

    //  Reproject
    Project(view_mode ? field_of_view : 0, aspect_ratio, zoom);

    //  Animate if requested
    //glutIdleFunc( move_light ? idle : NULL);

    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}
void Idle(){
    // Where time should be tracked
    glutPostRedisplay();                // indicates current window needs redisplaying (change has occured)
}
void Fatal(const char* error_message){
   cout << error_message << endl;
   exit(0);
}
void Init(){
    azimuth = 0;
    elevation = 0;
}


//___Main__________________________________________________________________________________________________________________

int main() {
    Init();         // initialize

    // Set null arguments and initialize GLUT
    int arg_c = 0;
    char* arg_v[1] = {(char*)"Nothing"};
    glutInit(&arg_c, arg_v);                                        // initialize GLUT
    
    // Display Window
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);       // (true color | z buffering | double buffered)
        // Double buffering allows concurrent drawing on one buffer and display on another
    glutInitWindowSize(600,600);                                    // size window 
    glutCreateWindow("Game");                                       // name window

    #ifdef USEGLEW
        if(glewInit() != GLEW_OK) Fatal("ERROR: Failed to Initialize GLEW");
    #endif

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