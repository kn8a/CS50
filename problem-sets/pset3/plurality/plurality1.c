#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes

void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }



    int voter_count = get_int("Number of voters: ");
    string name=0;


    // Loop over all voters

    for (int i = 0; i < voter_count; i++)
    {
        bool valid_name=false;
        do
        {
            name = get_string("Vote: ");
            for (int n = 0; n < candidate_count; n++)
            {
                if (strcmp(name, candidates[n].name)==0)
                {
                    valid_name=true;
                }
            }
            
            if (valid_name==false)
            {
                printf("Invalid vote.\n");
            }
        }
        while (valid_name!=false);


        if (strcmp(name, candidates[i].name)==0)
        {
            for (int v = 0; v < candidate_count; v++)
            {
                if (strcmp(name, candidates[i].name)==0)
                {
                    candidates[i].votes++;
                }
            }
        }

        // Check for invalid vote


    }

    // Display winner of election
    print_winner();
}


// Print the winner (or winners) of the election
void print_winner(void)
{
    int max=0;
    for (int i=0; candidate_count>i; i++)
    {
        if (candidates[i].votes>max)
        {
            max=candidates[i].votes;
        }
    }
    for (int i=0; candidate_count>i; i++)
    {
        if (candidates[i].votes==max)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    // TODO
    return;
}