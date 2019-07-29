/*
********************************************************************************
KnowledgeParser.h

Knowledge files use big-endian encoding for bytes read.
Copyright (C) 2019  Luka Micheletti

********************************************************************************
*/

#ifndef __KNOWLEDGE_PARSER__
#define __KNOWLEDGE_PARSER__

#include "Parser.h"
#include "Knowledge.h"

namespace Oort {
    class KnowledgeParser : public Parser {
    public:
        static const char HEADER_SEPARATOR;
        static const char PRIMARY_SEPARATOR;
        static const char SECONDARY_SEPARATOR;
        static const uint8_t HEADER_LENGTH;

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
}

#endif
