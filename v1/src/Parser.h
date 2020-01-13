#ifndef __PARSER__
#define __PARSER__

#include "utils.h"

namespace Oort {
    class Parser {
    public:
        // Read data from a file and store it.
        virtual void readFile(char* fileName) = 0;

        // Write stored data in a file.
        virtual void writeFile(char* fileName) = 0;
    };
}

#endif
