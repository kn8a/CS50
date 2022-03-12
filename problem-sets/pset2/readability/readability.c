#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>



int count_letters(string word);

int main(void)
{
    //prompt user text
    string text = get_string("enter text: ");
    //run counter function
    int grade = count_letters(text);
    //
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

//counting function
int count_letters(string word)
{
    int letters = 0;
    int sentences = 0;
    int words = 1;
    float grade = 0;

    //counting
    int count = 0;
    while (word[count] != 0)
    {
        if (word[count] > 64 && word[count] < 91)
        {
            letters++;
        }
        else if (word[count] > 96 && word[count] < 123)
        {
            letters++;
        }
        else if (word[count] == 33 || word[count] == 46 || word[count] == 63)
        {
            sentences++;
        }
        else if (word[count] == 32)
        {
            words++;
        }
        count++;
    }
    float L = ((float) letters * 100) / words;
    float S = ((float) sentences * 100) / words;
    //grade calculation
    grade = round(L * 0.0588 - S * 0.296 - 15.8);
    //return
    return grade;
}