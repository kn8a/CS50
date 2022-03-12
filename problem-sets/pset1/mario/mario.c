#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get user input
    int n;
    do
    {
        n = get_int("Enter size of pyramid: ");
    }
    while (n < 1 || n > 8);

    //loop
    for (int i = 0; i < n; i++)
    {
        //print spaces
        for (int s = (n - i - 2); s >= 0; s--)
        {
            printf(" ");
        }
        //print ladders
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}