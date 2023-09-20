// Implements a dictionary's functionality

#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

typedef struct linkedList {
    node *start;
    node *end;
}
linkedList;



// TODO: Choose number of buckets in hash table
static const uint_fast16_t tableSize = (26 * 10000) + (26 * 100) + 26 + (LENGTH);
static uint_fast32_t numberOfWords = 0;

// Hash table
static linkedList table[tableSize] = {{NULL,NULL}};

inline static int listAppend(const char word[LENGTH+1], linkedList *target){

    node *newNode = malloc(sizeof(node));
    if (newNode == NULL) {
        return 1;
    }

    strcpy((char*)newNode->word,(char*)word);
    newNode->next = NULL;
    // if target end is uninitialized.
    if (target->end == NULL) {

        target->start = newNode;
        target->end = newNode;
    }
    else
    {
        target->end->next = newNode;
        target->end = newNode;
    }
    // check if malloc was successful.
    return 0;
}
inline static node *listFind(const char word[LENGTH+1], const linkedList target){
    node *currentNode = target.start;
    while (currentNode != NULL) {
        if (strcmp((char*)currentNode->word,(char*)word) == 0) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return NULL;
}

// Returns true if word is in dictionary, else false

bool check(const char *word)
{
    static char newWord[LENGTH+1];
    strcpy((char*)newWord,(char*)word);
    for(uint_fast8_t i = 0; newWord[i]; i++){
      newWord[i] = toupper(newWord[i]);
    }

    const node *tmp = listFind(newWord,table[hash((char*)newWord)]);
    return (tmp == NULL) ? false : true;
}

// Hashes word to a number.
// must be given a lowercase string.
inline unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    const uint_fast16_t length = strlen((char*)word);
    const uint_fast16_t firstChar = word[0] - '@';
    const uint_fast16_t middlechar = word[length / 2] - '@';
    const uint_fast16_t lastChar = word[length] - '@';
    return (firstChar * 10000) + (middlechar * 100) + (lastChar) + (length);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // create file handle.
    FILE* file = NULL;
    // open file
    file = fopen(dictionary,"r");
    // check file opened
    if (file == NULL) {
        return false;
    }
    // get size of file.
    fseek(file,0,SEEK_END);
    uint_fast32_t size = ftell(file);
    // read words into memory
    uint_fast8_t words[size];
    rewind(file);
    fread(&words, sizeof(char*), size, file);
    char word[LENGTH];
    uint_fast8_t letterIndex = 0;
        for (register uint_fast16_t i = 0; i < size; i++) {
            register char c = toupper(words[i]);
            if (c == '\n') {
                // push into table.
                word[letterIndex] = '\0';
                unsigned int wordHash = hash((char*)word);
                listAppend(word, &table[wordHash]);
                numberOfWords++;
                letterIndex = 0;
            }
            else {
                    word[letterIndex] = c;
                    letterIndex++;
            }
        }
    // close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return numberOfWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    
    for (uint_fast16_t i = 0; i < tableSize; i++) {
        // don't bother if it's an empty list.
        if (table[i].start != NULL) {
            node *current = table[i].start;
            while (current->next != NULL) {
                node *tmp = current;
                current = current->next;
                free(tmp);
            }
            free(current);
        }
    }
    return true;
}
