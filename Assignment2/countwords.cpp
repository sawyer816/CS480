/* FILEHEADER
 * Sawyer Thompson
 * RedID: 823687079
 * February 28, 2022
 * CS 480-3
 * Professor Shen
 *
 *  Description: countwords cpp that runs the countwords thread
 *  and does the logic to count the number of words in the dictionary
 *  that have the given word as a prefix. 
 */

#include "countwords.h"

// using a prefix node, we are able to recursively traverse the dict tree
int countWords(dictNode *prefix)
{
    // base case
    if (!prefix)
    {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < ALPHABETSIZE; ++i)
    {
        // adds count to the next pointer
        count += countWords(prefix->next[i]);
    }
    // only adds to count if current node is a word
    if (prefix->isWord)
    {
        count++;
    }
    return count;
}

// reads in root node and file name
void *countwords(void *ptr)
{
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~"; // enables tokenization
    std::ifstream dictstream;
    EXEC_STATUS *exec = (EXEC_STATUS *)ptr; // initializes exec_status ptr
    struct stat buffer;
    stat(exec->filePath[TESTFILEINDEX], &buffer);
    exec->totalNumOfCharsInFile[TESTFILEINDEX] = buffer.st_size;
    while (!exec->taskCompleted[0])
    {
    } // ensures that this thread waits for completetion of populate
    // initialize for file opening and writing
    dictstream.open(exec->filePath[1]);
    if (dictstream.is_open())
    {
        std::string line;
        std::ofstream output;
        output.open("output.txt");

        // grabs the amount of characters in the file
        struct stat buffer;
        stat(exec->filePath[TESTFILEINDEX], &buffer);
        int size = buffer.st_size;

        // initializes values in
        exec->totalNumOfCharsInFile[TESTFILEINDEX] = size;
        long wordlength = 0;
        long totalchar = 0;
        exec->numOfCharsProcessedFromFile[TESTFILEINDEX] = &totalchar;

        while (std::getline(dictstream, line))
        {
            char *char_arr;
            // std::cout << "hi";
            // transforms string to char
            char_arr = &line[0];
            char *word = strtok(char_arr, delimiters);
            wordlength = (long)line.length() + 1;
            while (word != nullptr)
            {

                exec->tree->add(exec->dictRootNode, word);

                exec->wordCountInFile[TESTFILEINDEX] += 1;
                // std::cout << *(exec->numOfCharsProcessedFromFile[TESTFILEINDEX]) << "\n";
                // searches the word and returns the prefix node
                dictNode *prefix = exec->tree->findEndingNodeOfAStr(exec->dictRootNode, word);
                if (countWords(prefix) >= exec->minNumOfWordsWithAPrefixForPrinting)
                {
                    // std::cout<<exec->minNumOfWordsWithAPrefixForPrinting;
                    // prefix node used to print out the amount of words in dictionary
                    // that begin with prefix
                    output << word << " " << countWords(prefix) << "\n";
                }
                word = strtok(NULL, delimiters);
            }

            totalchar += wordlength;
        }
        output.close();
        dictstream.close();
        std::cout << std::endl
                  << "There are " << exec->wordCountInFile[TESTFILEINDEX] << " words in " << exec->filePath[TESTFILEINDEX] << "." << std::endl;
    }
    else
    {
        std::cout << "Unable to Open <<" << exec->filePath[TESTFILEINDEX] << ">>" << std::endl;
        exit(1);
    }
    return NULL;
};
