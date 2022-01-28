#ifndef dicttree_h
#define dicttree_h
#include <iostream>
#include <string.h> 
class dicttree {  
    struct dictNode{
    static const int NUMOfCHARS = 27;
    bool isWord;  
    struct dictNode *next[NUMOfCHARS];
    };

    public:
        //oid hi();
        void readInTree(char* FileName);
        bool add(dictNode* root, char *wordBeingInserted);
    //dictNode* findEndingNodeOfAStr(const char *remainingStr, const char *strBeingSearched);
    //void countWordsStartingFromANode(int &count);   
};
#endif