#include "glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

GLFWwindow* initGLFW()
{ 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window :c");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    return window;
}

char* readContent(const char* location)
{
    FILE* file = fopen(location, "r");
    char* fcontent = NULL;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    fcontent = malloc(size); 
    fread(fcontent, 1, size, file);

    fclose(file);
    return fcontent;
}

unsigned int loadVertexShader(const char* location)
{
    // Set up vertex shader and compile it
    unsigned int vertexShader;
    const char* vertexShaderSource = readContent(location);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR VERTEX SHADER COMPILATION FAILED %s", infoLog);
        return 0;
    }
    return vertexShader;
}

unsigned int loadFragmentShader(const char* location)
{
    // Set up fragment shader and compile it
    unsigned int fragmentShader;
    const char* fragmentShaderSource = readContent(location);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR VERTEX SHADER COMPILATION FAILED %s", infoLog);
        return 0;
    }
    return fragmentShader;
}