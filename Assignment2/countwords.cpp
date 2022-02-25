/* Sawyer Thompson
 * RedID: 823687079
 * January 25, 2021
 * CS 480-3
 * Professor Shen
 * 
 *  Description: Driver File that has methods necessary to read in a file and
    count the words present with a specified prefix in the dictionary tree
 */


#include "countwords.h"

//using a prefix node, we are able to recursively traverse the dict tree
int countWords(dictNode *prefix)
{
    //base case
    if (!prefix)
    {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < NUMOFCHARS; ++i)
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
void* countwords(void* ptr)
{
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    EXEC_STATUS *exec = (EXEC_STATUS*) ptr;
    //reads in file
    std::cout << "hi";
    std::ifstream dictstream(exec->filePath[1]);
    std::string line;
    while (std::getline(dictstream, line))
    {
        char *char_arr;
       // std::cout << "hi";
        // transforms string to char
        char_arr = &line[0];
        char *word = strtok(char_arr, delimiters);
        while (word != nullptr)
        {
            //searches the word and returns the prefix node
            dictNode *prefix = exec->tree->findEndingNodeOfAStr(exec->dictRootNode, word);
                std::cout << word << " ";
                // prefix node used to print out the amount of words in dictionary 
                // that begin with prefix
                std::cout << countWords(prefix) << "\n";
            word = strtok(NULL, delimiters);
        }
    }
};

