#include <stdio.h>
typedef FILE* Stream;
Stream StreamOpen(const char * filename);
int StreamReadInt(Stream stream);
float StreamReadFloat(Stream stream);
const char * StreamReadToken(Stream stream);
void StreamClose(Stream stream);
