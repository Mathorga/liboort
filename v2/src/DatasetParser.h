/*
********************************************************************************
DatasetParser.h

Implementation for parser of Dataset files (.knl).
Dataset files specification defines a header made of nine bytes, in order:
four byte for the inputs number, four for the outputs number and one for the
depth. The depth parameter is used to define the number of bytes used to encode
a single input or output value.
Dataset files use big-endian encoding for values.
For example, let's take a file containing the following bytes:
00    00    00    04    00    00    00    01    02    FA    0C    64    40    5D
BB    D1    9E    1F    80
The file contains a Dataset with experiences made of 4 input values and 1
output value.
Each value is two bytes long, so only one experience is stored in it.
Its input values are FA0C (0,9767605), 6440 (0,3916075), 5DBB (0,3661402) and
D19E (0,8188296).
Its output value is 1F80 (0,1230487).

Copyright (C) 2019  Luka Micheletti
********************************************************************************
*/

#ifndef __KNOWLEDGE_PARSER__
#define __KNOWLEDGE_PARSER__

#include "Parser.h"
#include "Dataset.h"

namespace Oort {
    class DatasetParser : public Parser {
    public:
        // Length of the header section of the file (in B).
        static const uint8_t HEADER_LENGTH;

        // Depth of the inputs number value (in B).
        static const uint8_t INPUTS_NUM_DEPTH;

        // Depth of the outputs number value (in B).
        static const uint8_t OUTPUTS_NUM_DEPTH;

        // Default depth of a single value, input or output (in B).
        static const uint8_t DEFAULT_VALUE_DEPTH;

        // Maximum depth of a single value, input or output (in B).
        static const uint8_t MAX_VALUE_DEPTH;

        DatasetParser();
        DatasetParser(Dataset* dataset);

        void readFile(char* fileName);
        void writeFile(char* fileName);

        // Getters.
        Dataset* getDataset();

        // Setters.
        void setDataset(Dataset* dataset);
        void setDepth(uint8_t depth);

    private:
        Dataset* dataset;
        uint8_t depth;
    };
}

#endif
