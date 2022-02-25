//Driver
#include "populatetree.h"
#include "countwords.h"
#include "dicttree.h"
#include <pthread.h>
//creates root node and returns it
dictNode *getRoot(void)
{
    struct dictNode *current = new dictNode;
    current->isWord = false;
    //ensures the node is clear
    for (int i = 0; i < NUMOFCHARS; i++){
        current->next[i] = nullptr;
    }
    return current;
}
void print_message_function(void){

}
int main(int argc, char **argv)
{
    std:: cout << "hi";
    EXEC_STATUS *ex = new EXEC_STATUS();
    ex->dictRootNode = new dictNode();
    std:: cout << ex->dictRootNode->isWord;
    ex->filePath[0] = argv[1];
    ex->filePath[1] = argv[2];
    std:: cout << ex->filePath[0];
    std:: cout << ex->filePath[1];
    pthread_t thread1;
    pthread_t thread2;
     //pthread_create( &thread1, NULL,
	 //		  &populate, *void ex);
     pthread_create( &thread1, NULL,
	 		  &populate, (void*) ex);

     pthread_join(thread1,NULL);

     pthread_create( &thread2, NULL,
	 		  &countwords, (void*) ex);
    
    pthread_join(thread2,NULL);
    pthread_exit(NULL);
    //creates a dicttree object
    dicttree *dictionary = new dicttree();
    // while
    // *numOfCharsProcessedFromFile[DICTSRCFILEINDEX] /  
    // totalNumOfCharsInFile[DICTSRCFILEINDEX] 
    // dictNode*root = getRoot();
    // dictionary->readInDict(root, argv[1]);
    // dictionary->readInTree(root, argv[2]);
};