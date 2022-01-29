/* Sawyer Thompson
 * RedID: 823687079
 * January 25, 2021
 * CS 480-3
 * Professor Shen
 * 
 *  Description: Driver File that has methods necessary to read in a file and
    count the words present with a specified prefix in the dictionary tree
 */

#include "dicttree.h"

//creates root node and returns it
dictNode *getRoot(void)
{
    struct dictNode *current = new dictNode;
    current->isWord = false;
    //ensures the node is clear
    for (int i = 0; i < current->NUMOfCHARS; i++){
        current->next[i] = nullptr;
    }
    return current;
}

//using a prefix node, we are able to recursively traverse the dict tree
int countWords(dictNode *prefix)
{
    //base case
    if (!prefix)
    {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < prefix->NUMOfCHARS; ++i)
    {
        //adds count to the next pointer 
        count += countWords(prefix->next[i]);
    }
    //only adds to count if current node is a word
    if (prefix->isWord)
    {
        count++;
    }
    return count;
}

//reads in root node and file name
void dicttree::readInTree(dictNode *root, char *FileName)
{
    //reads in file
    std::ifstream dictstream(FileName);
    std::string line;
    while (std::getline(dictstream, line))
    {
        char *char_arr;
        //transforms string to char
        char_arr = &line[0];
        char *word = strtok(char_arr, delimiters);
        while (word != nullptr)
        {
            //searches the word and returns the prefix node
            dictNode *prefix = findEndingNodeOfAStr(root, word);
                std::cout << word << " ";
                //prefix node used to print out the amount of words in dictionary 
                //that begin with prefix
                std::cout << countWords(prefix) << "\n";
            word = strtok(NULL, delimiters);
        }
    }
}

//Driver
int main(int argc, char **argv)
{
    //creates a dicttree object
    dicttree *dictionary = new dicttree();
    dictNode *root = getRoot();
    dictionary->readInDict(root, argv[1]);
    dictionary->readInTree(root, argv[2]);
};