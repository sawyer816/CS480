/* FILE HEADER
 * Sawyer Thompson
 * RedID: 823687079
 * February 28, 2021
 * CS 480-3
 * Professor Shen
 *
 *  Description: dicctree header file that provides the structure of a dictNode
 *  and declares variables that will be implemented in dicctree.cpp
 */

#ifndef dicttree_h
#define dicttree_h
#include <iostream>
#include <string.h>
#include <fstream>

#define ALPHABETSIZE 27

// defines a struct dictNode
struct dictNode
{
    bool isWord = false;
    struct dictNode *next[ALPHABETSIZE];
};

// defines a dicttree
class dicttree
{

public:
    // methods to be implemented
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    bool add(dictNode *root, char *wordBeingInserted);
    dictNode *findEndingNodeOfAStr(dictNode *root, char *strBeingSearched);
    void display(dictNode *root, char str[], int level);
};
#endif