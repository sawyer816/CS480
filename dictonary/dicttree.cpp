/* Sawyer Thompson
 * RedID: 823687079
 * January 25, 2021
 * CS 480-3
 * Professor Shen
 * 
 *  Description: dicctree cpp file that implements methods provided 
 *  in the header file to create and use a dictionary tree
 */

#include "dicttree.h"
//creates a new dictNode and returns it
dictNode *newNode(void)
{
    struct dictNode *current = new dictNode;
    current->isWord = false;
    //ensures the node is clear
    for (int i = 0; i < current->NUMOfCHARS; i++)
        current->next[i] = nullptr;
    return current;
}

//adds the parametized wordBeingInserted into the dictionary tree
bool dicttree::add(dictNode *root, char *wordBeingInserted)
{
    //creates an defines an instance of the struct
    struct dictNode *current = root;
    for (int i = 0; i < strlen(wordBeingInserted); i++)
    {
        //converts wordBeingSearched to lower case
        char currentLetter = std::tolower(wordBeingInserted[i]);
        int level;
        //edge case to ensure that ' character is the 27th character in the alphabet
        if (currentLetter == '\'')
        {
            level = 26;
        }
        //checks if letter is in the alphabet
        else if (isalpha(currentLetter))
        {
            //sets letter's level to 0-25
            level = currentLetter - 'a';
        }
        else
        {
            //ensures that only valid dictionary symbols are added
            std::cout << "Invalid Symbol: "<< currentLetter;
            return false;
        }
        //checks if there is already a node following the current node
        if (!current->next[level])
        {
            current->next[level] = newNode();
        }
        //moves to next node
        current = current->next[level];
    }
    //successfully added which means the final node is a word
    current->isWord = true;
    return true;
}

dictNode *dicttree::findEndingNodeOfAStr(dictNode *root, char *wordBeingSearched)
{
    //creates an defines an instance of the struct
    struct dictNode *current = root;
    for (int i = 0; i < strlen(wordBeingSearched); i++)
    {
        //converts wordBeingSearched to lower case
        char currentLetter = std::tolower(wordBeingSearched[i]);
        int level;
        if (currentLetter == '\'')
        {
            level = 26;
        }
        //checks if letter is in the alphabet
        else if (isalpha(currentLetter))
        {
            //sets letter's level to 0-25
            level = currentLetter - 'a';
        }
        else
        {
            return nullptr;
        }
        //returns null if there is no node to follow current node
        if (!current->next[level])
        {
            return nullptr;
        }
        //moves to next node
        current = current->next[level];
    }
    return current;
};

//reads in root and filename to build the dictionary tree
void dicttree::readInDict(dictNode *root, char *FileName)
{
    //reads file
    std::ifstream dictstream(FileName);
    std::string line;
    while (std::getline(dictstream, line))
    {
        char* char_arr;
        //converts line to character array
        char_arr = &line[0];
        //ensures that words are correctly tokenized in dictionary file
        char *word = strtok(char_arr, delimiters);
        while (word != nullptr)
        {
         std:: cout<< word;

            //adds word to the dictionary tree
            add(root, word);
            word = strtok(NULL, delimiters);
        }
    }
}
