#include "glad.h"
#include <GLFW/glfw3.h>

struct Mesh
{
    Vertex vertices[3];    
    unsigned int EBO, VAO, VBO;
};

typedef struct
{
    float x;
    float y;
    float z;
}Vertex;


Mesh_Create()
{
    malloc();
}


Mesh_Free()
{
    free();
}

readMesh()
{

}