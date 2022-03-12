#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int y = 0;
    float x;
    int c = 0;
    //get user input
    do
    {
        x = get_float("Change owed: $");
    }
    while (x < 0 || x == 0);

    x = round(x * 100);

    //count querters
    while (x - 25 >= 0)
    {
        y++;
        x = x - 25;
    }
    //count dimes
    while (x - 10 >= 0)
    {
        y++;
        x = x - 10;
    }
    //count nickels
    while (x - 5 >= 0)
    {
        y++;
        x = x - 5;
    }
    //count pennies
    while (x - 1 >= 0)
    {
        y++;
        x = x - 1;
    }
    //print number of coins
    printf("%i\n", y);
}