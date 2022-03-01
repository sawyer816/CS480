/* FILEHEADER
 * Sawyer Thompson
 * RedID: 823687079
 * February 28, 2021
 * CS 480-3
 * Professor Shen
 *
 *  Description: dicctree cpp file that implements methods provided
 *  in the header file to create and use a dictionary tree
 */

// Included Files
#include "populatetree.h"
#include "execstatus.h"

/* creates a new dictNode and returns it */
dictNode *newNode(void)
{
    struct dictNode *current = new dictNode;
    current->isWord = false;
    // ensures the node is clear
    for (int i = 0; i < ALPHABETSIZE; i++)
        current->next[i] = nullptr;
    return current;
}

/* adds the parametized wordBeingInserted into the dictionary tree */
bool dicttree::add(dictNode *root, char *wordBeingInserted)
{
    // creates an defines an instance of the struct
    struct dictNode *current = root;
    for (int i = 0; i < strlen(wordBeingInserted); i++)
    {
        char currentLetter = std::tolower(wordBeingInserted[i]); // converts wordBeingSearched to lower case
        int level;
        // edge case to ensure that ' character is the 27th character in the alphabet
        if (currentLetter == '\'')
        {
            level = ALPHABETSIZE - 1;
        }
        // checks if letter is in the alphabet
        else if (isalpha(currentLetter))
        {
            level = currentLetter - 'a'; // sets letter's level to 0-25
        }
        else
        {
            std::cout << "Invalid Symbol: " << currentLetter; // ensures only valid dictionary symbols are added
            return false;
        }
        // checks if there is already a node following the current node
        if (!current->next[level])
        {
            current->next[level] = newNode();
        }
        current = current->next[level]; // moves to next node
    }
    current->isWord = true; // successfully added
    return true;
}

/*Finds the ending node of the string and returns it */
dictNode *dicttree::findEndingNodeOfAStr(dictNode *root, char *wordBeingSearched)
{
    struct dictNode *current = root; // creates an defines an instance of the struct
    for (int i = 0; i < strlen(wordBeingSearched); i++)
    {
        char currentLetter = std::tolower(wordBeingSearched[i]); // converts wordBeingSearched to lower case
        int level;
        if (currentLetter == '\'')
        {
            level = ALPHABETSIZE - 1;
        }
        // checks if letter is in the alphabet
        else if (isalpha(currentLetter))
        {
            level = currentLetter - 'a'; // sets letter's level to 0-25
        }
        else
        {
            return nullptr;
        }
        // returns null if there is no node to follow current node
        if (!current->next[level])
        {
            return nullptr;
        }
        current = current->next[level]; // moves to next node
    }
    return current;
};
