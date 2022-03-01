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

//include file
#include "populatetree.h"

/*
 * populate thread, a worker thread that populates the dicttree with
 * the given values in the dictionary file.
*/
void *populate(void *ptr)
{
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~"; //defines delimiters
    std::ifstream dictstream;//initialize ifstream

    EXEC_STATUS *exec = (EXEC_STATUS *)ptr; // initualize exec_status exec

    //finds and and sets the total number of characters in the file
    struct stat buffer;
    stat(exec->filePath[DICTSRCFILEINDEX], &buffer);
    exec->totalNumOfCharsInFile[DICTSRCFILEINDEX] = buffer.st_size;

    //opens the stream and checks that it is a valid filepath
    dictstream.open(exec->filePath[DICTSRCFILEINDEX]);
    if (dictstream.is_open())
    {
        //initialize necessary variables 
        std::string line;
        long wordlength;
        long totalchar;
        char *char_arr;
        exec->wordCountInFile[DICTSRCFILEINDEX] = 0;
        exec->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = &totalchar;
        while (std::getline(dictstream, line))
        {
            char_arr = &line[0];                       // //converts line to character array
            char *word = strtok(char_arr, delimiters); // /tokenizes words
            while (word != nullptr)
            {
                wordlength = (long)strlen(word); // adds word to the dictionary tree
                exec->tree->add(exec->dictRootNode, word);
                totalchar += wordlength + 1;

                // std::cout << *(exec->numOfCharsProcessedFromFile[DICTSRCFILEINDEX]) << "\n";
                exec->wordCountInFile[DICTSRCFILEINDEX] += 1;
                word = strtok(NULL, delimiters);
            }
        }
        std::cout << std::endl
                  << "There are " << exec->wordCountInFile[DICTSRCFILEINDEX] << " words in " << exec->filePath[DICTSRCFILEINDEX] << "." << std::endl;
        dictstream.close();
    }
    else
    {
        std::cout << "Unable to Open <<" << exec->filePath[DICTSRCFILEINDEX] << ">>" << std::endl;
        exit(1);
    }
    return NULL;
};
