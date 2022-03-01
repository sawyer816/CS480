/* FILEHEADER
 * Sawyer Thompson
 * RedID: 823687079
 * February 28, 2022
 * CS 480-3
 * Professor Shen
 *
 *  Description: main cpp file that runs and joins two threads
 *  and checks for optional arguements
 */

// Included Files
#include "populatetree.h"
#include "countwords.h"
#include <unistd.h>

/* progressbar helper function */
void printProgressBar(int result)
{
    if (result == 0)
    {
        std::cout << HASHSYMBOL;
    }
    else
    {
        std::cout << PROGRESSSYMBOL;
    }
}

/* facilitates the progress bar of the threads */
void progressBar(EXEC_STATUS *ex)
{
    // variable initialization
    double curInterval;
    double progress;
    int count;

    // variables needed for the struct
    double dictCharsProcessed;
    double dictTotalChars;
    double testFileCharsProcessed;
    double testFileTotalChars;

    // hash and mark definitions
    int hash = ex->hashmarkInterval;
    int mark = ex->numOfProgressMarks;

    double interval = (100.000 / mark); // interval of each mark

    // runs first thread
    while (!ex->taskCompleted[DICTSRCFILEINDEX])
    {
        dictCharsProcessed = *(ex->numOfCharsProcessedFromFile[DICTSRCFILEINDEX]); // gets chars processed in the file
        dictTotalChars = ex->totalNumOfCharsInFile[DICTSRCFILEINDEX];              // gets total chars processed in the file
        progress = 100 * (dictCharsProcessed / dictTotalChars);                    // gets the progress %

        // checks if progress is greater than interval
        if (progress > curInterval && progress < 100)
        {
            count++;                   // increases count of PROGRESSSYMBOL
            int result = count % hash; // checks if Hash Interval is in correct location
            printProgressBar(result);
            curInterval += interval; // updates interval with percent needed
            std::cout.flush();
        }

        // checks if progress is finished
        if (progress == 100)
        {
            ex->taskCompleted[DICTSRCFILEINDEX] = true;
        }
    }

    // resets variables
    count = 0;
    curInterval = 0;

    // runs second thread
    while (!ex->taskCompleted[TESTFILEINDEX])
    {
        testFileCharsProcessed = *(ex->numOfCharsProcessedFromFile[TESTFILEINDEX]); // gets chars processed in the test file
        testFileTotalChars = ex->totalNumOfCharsInFile[TESTFILEINDEX];              // gets total chars  in the test file
        progress = 100 * (testFileCharsProcessed / testFileTotalChars);             // gets the progress %
        if (progress > curInterval && progress < 100)
        {
            count++; // increases count of PROGRESSSYMBOL
            int result = count % hash;
            printProgressBar(result);
            std::cout.flush();
            curInterval += interval;
        }

        // checks if progress is finished
        if (progress == 100)
        {
            ex->taskCompleted[TESTFILEINDEX] = true;
        }
    }
};

/* Driver Function */
int main(int argc, char *argv[])
{
    // initialize variables
    int opt;
    long initialized;

    // initialize struct
    EXEC_STATUS *ex = new EXEC_STATUS();

    // initialize variables in struct to defaults
    ex->numOfCharsProcessedFromFile[NUMOFFILES - 1] = new (long);
    ex->dictRootNode = new dictNode();
    ex->minNumOfWordsWithAPrefixForPrinting = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;
    ex->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = &initialized;
    ex->numOfCharsProcessedFromFile[TESTFILEINDEX] = &initialized;
    ex->hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
    ex->numOfProgressMarks = DEFAULT_NUMOF_MARKS;
    ex->minNumOfWordsWithAPrefixForPrinting = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;

    // ensures there is at least 2 argumenets
    if (argv[optind] == NULL || argv[optind + 1] == NULL)
    {
        printf("Mandatory argument(s) missing\n");
        exit(1);
    }

    // sets the path names
    int path = DICTSRCFILEINDEX;
    for (; optind <= NUMOFFILES; optind++)
    {
        ex->filePath[path] = argv[optind];
        path = TESTFILEINDEX;
    }

    // goes through optional arguements using getopt
    while ((opt = getopt(argc, argv, ":n:p:h:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            ex->minNumOfWordsWithAPrefixForPrinting = atoi(optarg);
            if (ex->numOfProgressMarks < MIN_NUMOF_MARKS)
            {
                std::cout << "Number of progress marks must be greater than " << MINNUMOFWORDS;
                exit(1);
            }
            break;
        case 'p':
            ex->numOfProgressMarks = atoi(optarg); // sets progressmarks
            // checks if numOfProgressMarks is the minimum
            if (ex->numOfProgressMarks < MIN_NUMOF_MARKS)
            {
                std::cout << "Number of progress marks must be a number and at least " << MIN_NUMOF_MARKS << std::endl;
                exit(1);
            }
            break;
        case 'h':
            ex->hashmarkInterval = atoi(optarg); // sets hash
            // checks if numOfProgressMarks is the minimum
            if (ex->hashmarkInterval > MAX_NUMOF_HASH)
            {
                std::cout << "Hash mark interval for progress must be a number, greater than 0, and less than or equal to " << MAX_NUMOF_HASH << std::endl;
                exit(1);
            }
            break;
        case '?': // checks if unkown option and exits
            printf("unknown option: %c\n", optopt);
            exit(1);
        }
    }

    // initialize threads
    pthread_t thread1;
    pthread_t thread2;

    // create threads
    pthread_create(&thread1, NULL, &populatetree, (void *)ex);
    pthread_create(&thread2, NULL, &countwords, (void *)ex);

    // runs progressBar
    progressBar(ex);

    pthread_exit(NULL);
    return 0;
};