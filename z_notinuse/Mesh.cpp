#include "../HeaderFiles/Import.h"         // Contains all necessary imports for OpenGL

Mesh::Mesh(float stx, float sty, float strx, float stry, float sts){
    start_x = stx;
    start_y = sty;
    stretch_x = strx;
    stretch_y = stry;
    step_size = sts;
    dimensions = 3;
    num_x_vertices = (int)((stretch_x/step_size) + 1);
    num_y_vertices = (int)((stretch_y/step_size) + 1);
    mesh_data_len = num_x_vertices*num_y_vertices*dimensions;
}
Mesh::~Mesh(){

}
float* Mesh::GenerateMeshData(){
    float mesh_data[mesh_data_len];
    //int indices[];

    //Getting length of array: int temp_square_length = *(&temp_square + 1) - temp_square;

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
            mesh_data[index] = x + i*step_size;      //x
            index++;
            mesh_data[index] = y + j*step_size;      //y
            index++;
            mesh_data[index] = z;                    //z   -->function inputs should be defined HERE    
            index++;
        }
    }
    //PrintMeshData(mesh_data);
    return mesh_data;
}
void Mesh::PrintMeshData(float *mesh_data){
    cout << "HERE" << endl;
    for(int i = 0; i < mesh_data_len; i++){
        if((i+1)%3 == 0){                   //end line on 3rd vertex (z)
            cout << mesh_data[i] << endl;
        }
        else{
            cout << mesh_data[i] << "   ";
        }
    }
}
void Mesh::RenderMeshDemo(float *mesh_data){
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
            glVertex3f(mesh_data[curr],  mesh_data[curr+1],  mesh_data[curr+2]);
            glVertex3f(mesh_data[curr+3],  mesh_data[curr+4],  mesh_data[curr+5]);
            glVertex3f(mesh_data[top_right_index],  mesh_data[top_right_index+1],  mesh_data[top_right_index+2]);
            glEnd();

            // Top triangle (red)
            glBegin(GL_TRIANGLES);
            glColor3f(0.5, 0, 0);           //red
            glVertex3f(mesh_data[top_right_index],  mesh_data[top_right_index+1],  mesh_data[top_right_index+2]);
            glVertex3f(mesh_data[top_left_index],  mesh_data[top_left_index+1],  mesh_data[top_left_index+2]);
            glVertex3f(mesh_data[curr],  mesh_data[curr+1],  mesh_data[curr+2]);
            glEnd();

            top_left_index +=3;
            top_right_index +=3;
        }
    }
}