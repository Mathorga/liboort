#ifndef __KNOWLEDGE__
#define __KNOWLEDGE__

#include "utils.h"

class Knowledge {
public:
    void readFile(char *fileName);

private:
    uint16_t inputsNum;
    uint16_t outputsNum;
    double **inputs;
    double **outputs;
};

#endif
