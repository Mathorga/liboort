/*
********************************************************************************
KnowledgeParser.h

Implementation of parser of Knowledge files (.knl).
Knowledge files specification defines a header made of three bytes, in order:
inputs number, outputs number and depth. The depth parameter is used to define
the number of bytes used to encode a single input or output value.
Knowledge files use big-endian encoding for values.
For example, let's take a file containing the following bytes:
04    01    02    FA    0C    64    40    5D    BB    D1    9E    1F    80
The file contains a knowledge with experiences made of 4 input values and 1
output value.
Each value is two bytes long, so only one experience is stored in it.
Its input values are fA0C (0,9767605), 6440 (0,3916075), 5DBB (0,3661402) and
D19E (0,8188296).
Its output value is 1F80 (0,1230487).

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
        static const uint8_t HEADER_LENGTH;
        static const uint8_t DEFAULT_DEPTH;

        KnowledgeParser();
        KnowledgeParser(Knowledge* knowledge);

        void readFile(char* fileName);
        void writeFile(char* fileName);

        // Getters.
        Knowledge* getKnowledge();

        // Setters.
        void setKnowledge(Knowledge* knowledge);
        void setDepth(uint8_t depth);

    private:
        Knowledge* knowledge;
        uint8_t depth;
    };
}

#endif
