#include "include/stream.h"

int main()
{
    Stream input;
    char* output;
    input = StreamOpen("input.txt");
    output = StreamReadToken(input);
    printf("%s", output);
    StreamClose(input);

    return 0;
}