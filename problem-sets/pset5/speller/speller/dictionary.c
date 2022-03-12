// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Not sure why a prime number is recommended to use for hash table size
// first try with table ~square root of total entries (10,007)
// afte different tries, higher numbers seem to produce better results. But higher than 500k is slower
const unsigned int N = 52579;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false - TODO ***
bool check(const char *word)
{

    // declare key variable
    unsigned int key = 0;
    // hash the word
    key = hash(word);
    // point cursor to first node in list at array location
    node *cursor = table[key];
    // traverse link list using cursor
    while (cursor != NULL)
    {
        // strcasecmp - compares strings
        if (strcasecmp(cursor->word, word) == 0)
        {
            //if found return true
            return true;
        }
        // next node
        else
        {
            cursor = cursor->next;
        }
        // when cursor = NULL  - end of list and no word
        if (cursor == NULL)
        {
            return false;
        }
    }
    return false;
}

// Hashes word to a number - COMPLETED !!
unsigned int hash(const char *word)
{
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(word);

    for (i = 0; i < key_len; i++)
    {
        // Not sure why a prime number is recommended to use in hash function, also 33 is common
        value = value * 37 + tolower(word[i]);
    }

    value = value % N;

    return value;
}

// word count variable
unsigned int wordcount = 0;
// Loads dictionary into memory, returning true if successful, else false

bool load(const char *dictionary)
{
    // declare hash key variable
    unsigned int key = 0;
    // fopen - check if not NULL - COMPLETED !!
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    // fscanf(file, "%s", word) - will return EOF at end of file (scanf("%d", &n) != EOF) - COMPLETED !!
    while (fscanf(dict, "%s", word) != EOF)
    {
        // node *n = malloc(sizeof(node)) - allocate mem for new node - check if not NULL - COMPLETED !!
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // hash the word () - TODO ***
        key = hash(word);
        // copy word int node - strcpy(n->word, word) - TODO ***
        strcpy(n->word, word);
        // n->next = NULL - TODO ***
        n->next = table[key];
        // set the new node to be the new first node - TODO ***
        table[key] = n;
        // count words
        wordcount++;

    }
    // close fopen for dict
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    // iterate through array
    for (int i = 0; i < N; i++)
    {
        // create cursor
        node *cursor = table[i];
        // while cursor is not NULL
        while (cursor != NULL)
        {
            // create temp
            node *temp = cursor;
            // move cursor
            cursor = cursor->next;
            // free temp
            free(temp);
        }

        // check that everything is freed
        if ((i == N - 1) && (cursor == NULL))
        {
            return true;
        }
    }

    return false;
}
