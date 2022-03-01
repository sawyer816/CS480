/* FILEHEADER
 * Sawyer Thompson
 * RedID: 823687079
 * February 28, 2022
 * CS 480-3
 * Professor Shen
 *
 *  Description: populatetree cpp that runs the populate thread
 *  and does the logic to put a given word from a file into a
 *  dictionary tree.
 */

// include file
#include "populatetree.h"

/*
 * populate thread, a worker thread that populates the dicttree with
 * the given values in the dictionary file.
 */
void *populatetree(void *ptr)
{
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~"; // enables tokenization
    std::ifstream dictstream;                                                    // initialize ifstream

    EXEC_STATUS *exec = (EXEC_STATUS *)ptr; // initualize exec_status exec

    // opens the stream and checks that it is a valid filepath
    dictstream.open(exec->filePath[DICTSRCFILEINDEX]);
    if (dictstream.is_open())
    {
        // initialize necessary variables
        std::string line;
        long wordlength;
        long totalchar;
        char *char_arr;

        // finds and and sets the total number of characters in the file
        struct stat buffer;
        stat(exec->filePath[DICTSRCFILEINDEX], &buffer);
        exec->wordCountInFile[DICTSRCFILEINDEX] = 0;
        exec->totalNumOfCharsInFile[DICTSRCFILEINDEX] = buffer.st_size;

        // sets necessary initialization for struct exec
        exec->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = &totalchar;

        // runs through the stream if there is a nextline
        while (std::getline(dictstream, line))
        {
            char_arr = &line[0];                       // converts line to character array
            char *word = strtok(char_arr, delimiters); // tokenizes words
            wordlength = (long)line.length() + 1;      // sets wordlength to the length of the line

            // checks each word in the line and makes sure it exists
            while (word != nullptr)
            {
                exec->tree->add(exec->dictRootNode, word);    // adds word to the dictionary tree
                exec->wordCountInFile[DICTSRCFILEINDEX] += 1; // increments the word count of the file
                word = strtok(NULL, delimiters);
                totalchar += wordlength; // increments the total chars by the line chars
            }
        }
        // prints the number of words in the file
        std::cout << std::endl
                  << "There are " << exec->wordCountInFile[DICTSRCFILEINDEX]
                  << " words in " << exec->filePath[DICTSRCFILEINDEX] << "." << std::endl;

        dictstream.close();
    }
    else // prints out message and exits if bad file
    {
        std::cout << "Unable to Open <<" << exec->filePath[DICTSRCFILEINDEX] << ">>" << std::endl;
        exit(1);
    }
    return NULL;
};
