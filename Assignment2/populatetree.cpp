#include "populatetree.h"
void* populate(void* ptr){
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    std:: cout << "               " <<std::endl;
    EXEC_STATUS *exec = (EXEC_STATUS*) ptr;
    
    std:: cout << exec->filePath[0];
    std:: cout << "ddddddd";
    std::ifstream dictstream(exec->filePath[0]);
    std::string line;
    while (std::getline(dictstream, line))
    {
         char* char_arr;
        // //converts line to character array
         char_arr = &line[0];
        // //ensures that words are correctly tokenized in dictionary file
          char *word = strtok(char_arr, delimiters);
        while (word != nullptr)
        {
            //adds word to the dictionary tree
            exec->tree->add(exec->dictRootNode, word);
            
            word = strtok(NULL, delimiters);
        }
    }
};

