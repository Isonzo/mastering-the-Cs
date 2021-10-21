#include <stdio.h> // printf and other goodies
#include <stdlib.h> // exit
#include <stdbool.h> // true and false
#include <string.h> // strlen()
#include <limits.h> // INT_MAX
#define MAXC 128 // Max characters in a line (very generous)

int calculateArea(char* dimensions);
int calculateRibbon(char* dimensions);

int main()
{
    char line[MAXC];
    FILE* file = fopen("input.txt", "r");
    int wrapping_paper = 0;
    if (file == NULL)
        exit(1);
    while(fgets(line, sizeof(line), file) != NULL)
    {
        wrapping_paper += calculateRibbon(line);
    }
    printf("%d\n", wrapping_paper);

    fclose(file);
    return 0;
}

int calculateArea(char* dimensions)
{
    bool checked = false;
    int d_count = 0;
    int box_dim[3];
    // Get the data and store it in box_dim
    for (unsigned int i = 0; i < strlen(dimensions); ++i)
    {

        if (dimensions[i] == 'x')
            checked = false;
        else if (!checked)
        {
            char * section = &dimensions[i];
            box_dim[d_count] = atoi(section);
            checked = true;
            d_count++;
        }
    }

    // Find surface area of the box (l w h are the corresponding dimensions)
    int l = box_dim[0];
    int w = box_dim[1];
    int h = box_dim[2];
    int first, second;

    int surface_area = 2*l*w + 2*w*h + 2*h*l;
    // Add the little extra
    first = second = INT_MAX;

    for (int i = 0; i < 3; ++i)
    {
        if (box_dim[i] < first)
        {
            second = first;
            first = box_dim[i];
        }
        else if (box_dim[i] < second)
        {
            second = box_dim[i];
        }
    }

    surface_area += first * second;

    return surface_area;
}

int calculateRibbon(char* dimensions)
{
    bool checked = false;
    int d_count = 0;
    int box_dim[3];
    // Get the data and store it in box_dim
    for (unsigned int i = 0; i < strlen(dimensions); ++i)
    {

        if (dimensions[i] == 'x')
            checked = false;
        else if (!checked)
        {
            char * section = &dimensions[i];
            box_dim[d_count] = atoi(section);
            checked = true;
            d_count++;
        }
    }

    // Find surface area of the box (l w h are the corresponding dimensions)
    int l = box_dim[0];
    int w = box_dim[1];
    int h = box_dim[2];
    int first, second;

    int volume = l * h * w;
    // Add the little extra
    first = second = INT_MAX;

    for (int i = 0; i < 3; ++i)
    {
        if (box_dim[i] < first)
        {
            second = first;
            first = box_dim[i];
        }
        else if (box_dim[i] < second)
        {
            second = box_dim[i];
        }
    }

    volume += 2*first + 2*second;

    return volume;
}