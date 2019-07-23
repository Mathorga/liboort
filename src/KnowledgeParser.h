#ifndef __KNOWLEDGE_PARSER__
#define __KNOWLEDGE_PARSER__

#include "Parser.h"
#include "Knowledge.h"

class KnowledgeParser : public Parser {
public:
    KnowledgeParser();
    KnowledgeParser(Knowledge* knowledge);

    void readFile(char* fileName);
    void writeFile(char* fileName);

    // Getters.
    Knowledge* getKnowledge();

    // Setters.
    void setKnowledge(Knowledge* knowledge);

private:
    Knowledge* knowledge;
};

#endif
