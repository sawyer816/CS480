#include "dicttree.h"              

struct dictNode {
    static const int NUMOfCHARS = 27;
    bool isWord;  
    struct dictNode *next[NUMOfCHARS];
    };
    
struct dictNode* newNode(){
  dictNode* node = new dictNode;
  node->isWord = false;
  return node;
}

bool dicttree::add(dictNode* root, char* wordBeingInserted){
   struct dictNode *current = root;
   for (int i = 0; i < strlen(wordBeingInserted); i++) {
     int level = wordBeingInserted[i] - 'a';
     if(!current->next[level]){
       current->next[level]= new dictNode;
     }
   }
   current->isWord = true;
   return true;
}
//void hi (){
//  std:: cout << hi;
//}
void dicttree::readInTree(char* FileName){
const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
//std::ifstream dictstream(filepath);
char *word = strtok(FileName, delimiters);
dictNode* root = new dictNode;
    while (word != nullptr) 
    { 
      std::cout<< "test";
      add(root, word);
      // call add method to insert word to build the dictionary tree 
      //...... 
      // handle error from insertion result 
      //..... 
      
      // read next word 
      word = strtok(NULL, delimiters);  
    } 
}

