//Driver
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
int main(int argc, char **argv)
{
    //creates a dicttree object
    dicttree *dictionary = new dicttree();
    dictNode *root = getRoot();
    dictionary->readInDict(root, argv[1]);
    dictionary->readInTree(root, argv[2]);
};