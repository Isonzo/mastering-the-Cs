#include "include/stream.h"

int main()
{
    Stream input;
    float output;
    input = StreamOpen("input.txt");
    output = StreamReadFloat(input);
    printf("%f", output);
    StreamClose(input);

    return 0;
}