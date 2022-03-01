/* FILEHEADER
 * Sawyer Thompson
 * RedID: 823687079
 * February 28, 2022
 * CS 480-3
 * Professor Shen
 *
 *  Description: header file that defines populate tree worker thread
 */

//included files
#include "dicttree.h"
#include "execstatus.h"

/*
 * Worker thread that puts the words in a dictionary
 * into a trie tree.
 */
void *populate(void *);