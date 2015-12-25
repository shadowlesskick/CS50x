/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define HASHTABLE_SIZE 200000

void addToDictionary(const char* word);
void lower_string(char*);

// linked-list of 
typedef struct collisionNode
{
    char* word;
    struct collisionNode* next;
} collisionNode;

collisionNode* hashtable;
int numberOfEntries = 0;

/**
 * Returns true if word is in dictionary else false.
 * Case insensitive
 */
bool check(const char* word)
{
    char* word1 = malloc((strlen(word)+1)*sizeof(char));
    strcpy(word1, word);
    lower_string(word1);
    unsigned long hashnum = hash(word1) % HASHTABLE_SIZE;
    collisionNode * node = &hashtable[hashnum];
    
    while(1)
    {
        if(node->word == NULL)
        {
            free(word1);
            return false;
        }
        else
        {
            if(strcmp(node->word,word1) == 0)
            {
                free(word1);
                return true;
            }
            else
            {
                if(node->next == NULL)
                {
                    free(word1);
                    return false;
                }
                else
                {
                    node = node->next;
                }
            }
        }   
    }
    free(word1);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    hashtable = malloc(sizeof(collisionNode)*HASHTABLE_SIZE);
    char* word = malloc((LENGTH+1)*sizeof(char));
    
    int index = 0;
    
    for (int c = fgetc(inptr); c != EOF; c = fgetc(inptr))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            word[index] = c;
            index++;

            // ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // consume remainder of alphabetical string
                while ((c = fgetc(inptr)) != EOF && isalpha(c));

                // prepare for new word
                index = 0;
            }
        }
        
        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';
            
            if(check(word) == 0)
            {
                addToDictionary(word);
                numberOfEntries++;
            }
            

            // prepare for next word
            index = 0;
        }
    }
    
    free(word);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return numberOfEntries;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    collisionNode * node;
    for(int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node = &hashtable[i];
        while(1)
        {
            collisionNode* tmp = node->next;
            free(node->word);
            free(node);
            node = tmp;
            if(tmp == NULL)
            {
                //free(hashtable[i]);
                break;
            }
        }
    }
    return true;  
}

/**
 * dbj2 hash, popular hash found on the on internet: http://www.cse.yorku.ca/~oz/hash.html
 */
unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c = 0;

    while ((c = *str++) != 0)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

/**
 * adds word to the dictionary
 */
void addToDictionary(const char* word)
{
    unsigned long hashnum = hash(word) % HASHTABLE_SIZE;
    collisionNode *node = &hashtable[hashnum];
    while(1)
    {
        if(node->word == NULL)
            {
                node->word = malloc((LENGTH+1)*sizeof(char));
                strcpy(node->word,word);
                return;
            }
        else
        {
            if(node->next == NULL)
            {
                node->next = malloc(sizeof(collisionNode));
                node = (node->next);
                node->word = malloc((LENGTH+1)*sizeof(char));
                strcpy(node->word, word);
                node->next = NULL;
                return;
                
            }
            else
            {
                node = (node->next);
            }
        }  
    }
}

/**
 * changes characters in string to lowercase (http://forgetcode.com/C/568-Change-string-to-lower-case-without-strlwr)
 */
void lower_string(char *string)
{
   while(*string)
   {
      if ( *string >= 'A' && *string <= 'Z' )
      {
         *string = *string + 32;
      }
      string++;
   }
}

