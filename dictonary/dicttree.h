/* Sawyer Thompson
 * RedID: 823687079
 * January 25, 2021
 * CS 480-3
 * Professor Shen
 * 
 *  Description: dicctree header file that provides the structure of a dictNode
 *  as it is used in both countwords.cpp and dicttree.cpp, and declares variables
 *  implemented in dicctree.cpp
 */

#ifndef dicttree_h
#define dicttree_h
#include <iostream>
#include <string.h>
#include <fstream>

//defines a struct dictNode
struct dictNode
{
    //number of characters in the alphabet
    static const int NUMOfCHARS = 27;
    bool isWord = false;
    struct dictNode *next[NUMOfCHARS];
};

//defines a dicttree
class dicttree
{
    
public:
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    //methods to be implemented
    void readInDict(dictNode *root, char *FileName);
    void readInTree(dictNode *root, char *wordBeingInserted);
    bool add(dictNode *root, char *wordBeingInserted);
    dictNode *findEndingNodeOfAStr(dictNode *root, char *strBeingSearched);
    void display(dictNode *root, char str[], int level);
};
#endif