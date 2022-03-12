#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Functions
    int hprint(void);
    int vprint(void);
    //Variables
    int vert;
    int hor;
    int spacing;
    int input;
    
    //Input
    do
    {
    input = get_int("Enter size of pyramid: ");
    }
    while (input < 1 || input > 9);

    hprint();
    vprint();

//Horizontal print
void hprint(int input);
{
    printf("*");
}

//Vertical print
void vprint(int input);
{
    printf("\n");
} 



}

