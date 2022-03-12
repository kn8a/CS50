#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    //confirm 2nd argument
    if (argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //confirm integer
    bool nonum = false;
    int s = 0;
    while (argv[1][s] != 0)
    {
        if (argv[1][s] < 48 || argv[1][s] > 57)
        {
            nonum = true;
        }
        s++;
    }
    //confirm 2 arguments and validate integers
    if (argc != 2 || nonum == true)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //key to integer
    int k = atoi(argv[1]);

    //get text
    string text = get_string("plaintext: ");

    //ciphering text
    char cipher[strlen(text)];
    printf("ciphertext: ");

    for (int i = 0; strlen(text) != i; i++)
    {
        //ciphering upper chase
        if (text[i] > 64 && text[i] < 91)
        {
            cipher[i] = (((text[i] - 65) + k) % 26) + 65;
            printf("%c", cipher[i]);
        }
        //ciphering lower text
        else if (text[i] > 96 && text[i] < 123)
        {
            cipher[i] = (((text[i] - 97) + k) % 26) + 97;
            printf("%c", cipher[i]);
        }
        //moving other characters
        else
        {
            cipher[i] = text[i];
            printf("%c", cipher[i]);
        }
    }
    printf("\n");
}