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

/* uses a prefix node, to recursively traverse the dict tree */
int countWords(dictNode *prefix)
{
    int count = 0; // initialize counter
    // base case
    if (!prefix)
    {
        return 0;
    }
    // checks for each letter
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

/*
 * countwords thread, a worker thread that counts the words of a dictionary
 * that have the given prefix of a word in another file.
 */
void *countwords(void *ptr)
{
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~"; // enables tokenization
    std::ifstream dictstream;                                                    // initialize ifstream

    EXEC_STATUS *exec = (EXEC_STATUS *)ptr; // initializes exec_status ptr

    // while loop to ensure thread doesn't start before the completion of the thread populate
    while (!exec->taskCompleted[0])
    {
    }

    // opens the stream and checks that it is a valid filepath
    dictstream.open(exec->filePath[1]);
    if (dictstream.is_open())
    {
        // initialize necessary variables
        std::string line;
        long wordlength = 0;
        long totalchar = 0;
        char *char_arr;

        // creates and opens an output file named countwords_output.txt
        std::ofstream output;
        output.open("countwords_output.txt");

        // finds and and sets the total number of characters in the file
        struct stat buffer;
        stat(exec->filePath[TESTFILEINDEX], &buffer);
        int size = buffer.st_size;
        exec->totalNumOfCharsInFile[TESTFILEINDEX] = size;

        // sets necessary initialization for struct exec
        exec->numOfCharsProcessedFromFile[TESTFILEINDEX] = &totalchar;

        // runs through the stream if there is a nextline
        while (std::getline(dictstream, line))
        {
            char_arr = &line[0];                       // converts line to character array
            char *word = strtok(char_arr, delimiters); // tokenizes words
            wordlength = (long)line.length() + 1;      // sets wordlength to the length of the line

            // checks each word in the line and makes sure it exists
            while (word != nullptr)
            {
                exec->wordCountInFile[TESTFILEINDEX] += 1;
                // sets prefix to the last node of word
                dictNode *prefix = exec->tree->findEndingNodeOfAStr(exec->dictRootNode, word);

                // checks and increments the number of times the prefix is in the dictionary
                if (countWords(prefix) >= exec->minNumOfWordsWithAPrefixForPrinting)
                {
                    output << word << " " << countWords(prefix) << "\n";
                }
                word = strtok(NULL, delimiters);
            }
            totalchar += wordlength; // increments the total chars by the line chars
        }
        output.close();
        dictstream.close();
        // prints the number of words in the file
        std::cout << std::endl
                  << "There are " << exec->wordCountInFile[TESTFILEINDEX]
                  << " words in " << exec->filePath[TESTFILEINDEX] << "." << std::endl;
    }
    else // prints out message and exits if bad file
    {
        std::cout << "Unable to Open <<" << exec->filePath[TESTFILEINDEX] << ">>" << std::endl;
        exit(1);
    }
    return NULL;
};
