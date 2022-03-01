/* FILEHEADER
 * Sawyer Thompson
 * RedID: 823687079
 * February 28, 2022
 * CS 480-3
 * Professor Shen
 *
 *  Description: header file that defines countwords worker thread
 */

// Included Files
#include "execstatus.h"
#include <pthread.h>

/*
 * Worker thread that counts the number of times a word in a file
 * is prefixxed in a dictionary.
 */
void *countwords(void *);
