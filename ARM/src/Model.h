#ifndef __MODEL__
#define __MODEL__

#include "Neuron.h"
#include "utils.h"

class Model {
public:
    virtual void print() = 0;
    uint32_t getInputsNum();
    uint32_t getOutputsNum();
    uint32_t getHiddensNum();
    uint32_t getNeuronsNum();
    Neuron* getNeurons();

protected:
    // Number of input neurons.
    uint32_t inputsNum;
    // Number of output neurons.
    uint32_t outputsNum;
    // Number of hidden neurons.
    uint32_t hiddensNum;
    // Total number of neurons.
    uint32_t neuronsNum;

    Neuron* neurons;
};

#endif
