#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

typedef FILE* Stream;
// Open a file for reading.
// Params:
//     filename = Name of the file to be opened for reading.
// Returns:
//     NULL if the file name is null or the file could not be opened.
//     Pointer to a FILE object if the file was opened successfully.
Stream StreamOpen(const char * filename)
{
    Stream file = fopen(filename, "r");
    if (!file)
        return NULL;
    return file;
}

// Read a single integer from a stream.
// (NOTE: Verify that the stream is valid first.)
// Params:
//     stream = The file stream from which to read.
// Returns:
//     If the stream was opened succesfully,
//       then return an integer value read from the file,
//       else return 0.
int StreamReadInt(Stream stream)
    {
        if (!stream) return 0;
        char* raw_value;
        int value;

        fgets(raw_value, BUFFER_SIZE, stream);
        value = atoi(raw_value);

        return value;
    }
// Read a single float from a stream.
// (NOTE: Verify that the stream is valid first.)
// Params:
//     stream = The file stream from which to read.
// Returns:
//     If the stream was opened succesfully,
//       then return a float value read from the file,
//       else return 0.
float StreamReadFloat(Stream stream)
{
    if (!stream) return 0;
    char* raw_value;
    float value;

    fgets(raw_value, BUFFER_SIZE, stream);
    value = atof(raw_value);

    return value;
}

// Read a token (a single word) from a file.
// Suggested steps:
//     - Set the first value in tokenBuffer to 0
//     - If the stream was opened successfully,
//       - Read a string ("%s") into tokenBuffer using fscanf_s()
//     - Return tokenBuffer
// Params:
//     stream = The file stream from which to read.
// Returns:
//     Pointer to tokenBuffer
const char * StreamReadToken(Stream stream)
{
    if (!stream) return 0;
    static char tokenBuffer[1000];
    tokenBuffer[0] = 0;
    fscanf(stream, "%s", tokenBuffer);
    
    return tokenBuffer;
}

// Close an opened stream.
// (NOTE: Do not attempt to close the stream if the pointer is null.)
// Params:
//     stream = The file stream to be closed.
void StreamClose(Stream stream)
{
    if (!stream) return;
    fclose(stream);
}