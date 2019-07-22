#ifndef __KNOWLEDGE_PARSER__
#define __KNOWLEDGE_PARSER__

#include "Knowledge.h"

class KnowledgeParser {
public:
    KnowledgeParser();
    KnowledgeParser(Knowledge* knowledge);

    void readFile(char* fileName);
    void writeFile(char* fileName);

    // Getters.
    Knowledge* getKnowledge();

    // Setters.
    void setData(Knowledge* knowledge);

private:
    Knowledge* knowledge;
};

#endif
