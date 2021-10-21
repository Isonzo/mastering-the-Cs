#include <stdio.h>
#include <stdbool.h>

int main()
{
    int input;
    int floor = 0;
    int position = 0;
    bool not_reached_basement = true;
    FILE *file;

    file = fopen("input.txt", "r");
    
    if (file)
    {
        while ((input = getc(file)) != EOF)
        {
            if (not_reached_basement)
                position++;

            if (input == '(')
                floor++;
            else if (input == ')')
                floor--;
            
            if (floor < 0)
                not_reached_basement = false;
        }
        fclose(file);
    }

    printf("Santa's target floor = %d\nPosition which he entered the basement: %d\n", floor, position);
    return 0;
}