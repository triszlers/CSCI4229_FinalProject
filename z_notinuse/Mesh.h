
#pragma once

class Mesh {
public:
    // Mesh data is generated upon instantiation
    Mesh(float start_x, float start_y, float stretch_x, float stretch_y, float step_size);
    ~Mesh();

    float* GenerateMeshData();
    void PrintMeshData(float* mesh_data);
    void RenderMeshDemo(float* mesh_data);      // renders mesh via glut triangles

private:
    float start_x;
    float start_y;
    float stretch_x;
    float stretch_y;
    float step_size;
    int dimensions;
    int num_x_vertices;
    int num_y_vertices;
    int mesh_data_len;
};