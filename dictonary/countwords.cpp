#include "dicttree.h"
   
int main(int argc, char **argv) {
    dicttree *dictionary = new dicttree();
    char* dict = "dictionary.txt";
    dictionary->readInTree(dict);
    std::cout << "hi";
    const char *word = "Helloo";
    std::cout << strlen(word);
};