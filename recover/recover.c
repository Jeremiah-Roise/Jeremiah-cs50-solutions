#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define BlockSize 512
 
struct byteRange
{
    size_t start;
    size_t end;
};
int findJPGS(FILE *file);

int main(int argc,  char *argv[])
{
    if (argc != 2)
    {
        printf("proper usage: ./recover IMAGE.raw\n");
        return 1;
    }
    // open image file for reading
    FILE *file = fopen(argv[1],  "r");
    if (file == NULL)
    {
        printf("could not open file for reading\n");
        return 1;
    }
    // read block and check for jpg.
    struct byteRange jpgs[50];
    int result = findJPGS(file);

    fclose(file);
    return result;
}


// returns the number of jpgs found.
int findJPGS(FILE *file)
{
    uint8_t block[BlockSize];
    size_t numberJpgs = 0;
    bool writingJPG = false;
    char fileName[50];
    FILE *output = NULL;
    // read every 512 byte block in the file.
    while (fread(&block,  sizeof(uint8_t),  BlockSize,  file))
    {
        // check every byte of every block for a byte pattern.
        for (size_t i = 0; i < BlockSize; i++)
        {
            // check if the next check will go out of bounds
            if (i + 4 > BlockSize)
            {
                break;
            }

            // check the first byte, second byte, third byte, and then check the first 4 bits of the fourth byte.
            //  |  first byte    |    |    second byte     |    |     third byte     |    |        fourth byte          |
            if ((block[i] != 0xff) || (block[i + 1] != 0xd8) || (block[i + 2] != 0xff) || ((block[i + 3] & 0xf0) != 0xe0))
            {
                break;
            }

            // valid jpg start found.
            // now write blocks until the next occurence
            
            if (output != NULL && writingJPG == true)
            {
                fclose(output);
                output = NULL;
                writingJPG = false;
            }

            if (output == NULL && writingJPG != true)
            {
                sprintf(fileName,  "%03lu.jpg", numberJpgs);
                output = fopen(fileName, "w");
                writingJPG = true;
                numberJpgs++;
            }
        }


        if (output != NULL && writingJPG)
        {
            // write image to file.

            if (output == NULL)
            {
                printf("could not open file for reading\n");
                return 1;
            }

            fwrite(&block, sizeof(uint8_t), BlockSize, output);
            // close file.
        }
    }
    if (output != NULL)
    {
        fclose(output);
        numberJpgs++;
    }
    return 0;
}





