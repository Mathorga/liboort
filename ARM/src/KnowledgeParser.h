#ifndef __KNOWLEDGE_PARSER__
#define __KNOWLEDGE_PARSER__

#include "Knowledge.h"

class KnowledgeParser {
    KnowledgeParser();
    KnowledgeParser(Knowledge* data);

    void readFile(char* fileName);
    void writeFile(char* fileName);

    // Getters.
    Knowledge* getData();

    // Setters.
    void setData(Knowledge* data);

private:
    Knowledge* data;
};

#endif
