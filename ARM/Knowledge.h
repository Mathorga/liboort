#ifndef __KNOWLEDGE__
#define __KNOWLEDGE__

#include "utils.h"

class Knowledge {
public:
    void describe();

    uint16_t getInputsNum();
    uint16_t getOutputsNum();
    double** getInputs();
    double** getOutputs();

    void setInputsNum(uint16_t num);
    void setOutputsNum(uint16_t num);
    void setInputs(double** inputs);
    void setOutputs(double** outputs);

private:
    uint16_t inputsNum;
    uint16_t outputsNum;
    double** inputs;
    double** outputs;
};

#endif
