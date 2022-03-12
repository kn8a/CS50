#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;
BYTE buffer[512];

int main(int argc, char *argv[])
{
    //check two arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    //check file not NULL
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Could not open card.\n");
        return 2;
    }

    //declare variables
    int counter = 0;
    char filename[8];
    bool found = false;
    FILE *img = NULL;

    while (fread(&buffer, sizeof(buffer), 1, raw) == 1)

        //if new header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            found = true;
            fwrite(&buffer, sizeof(buffer), 1, img);
            counter++;
        }

        //if already found a file
        else if (found == true)
        {
            fwrite(&buffer, sizeof(buffer), 1, img);
        }

    //close input,output
    fclose(img);
    fclose(raw);
}