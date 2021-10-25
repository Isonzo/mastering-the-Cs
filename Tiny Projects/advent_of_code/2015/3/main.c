#include <stdio.h>
#include <search.h>

int main()
{
    int input;
    FILE* file = fopen("input.txt", "r");

    int x = 0;
    int y = 0;


    if (file)
    {
        while ((input = getc(file)) != EOF)
        {
            if (input == '^')
                ++y;
            else if (input == 'v')
                --y;
            else if (input == '>')
                ++x;
            else if (input == '<')
                --x;
            

        }
    }
    return 0;
}



typedef struct
{
    int x;
    int y;
}House;
