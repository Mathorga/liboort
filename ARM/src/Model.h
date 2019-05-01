#ifndef __MODEL__
#define __MODEL__

#include "Neuron.h"
#include "utils.h"

#define neurons_num_t uint32_t

class Model {
public:
    virtual void print() = 0;

    // Getters.
    neurons_num_t getInputsNum();
    neurons_num_t getOutputsNum();
    neurons_num_t getHiddensNum();
    neurons_num_t getNeuronsNum();

protected:
    // Number of input neurons.
    neurons_num_t inputsNum;
    // Number of output neurons.
    neurons_num_t outputsNum;
    // Number of hidden neurons.
    neurons_num_t hiddensNum;
    // Total number of neurons.
    neurons_num_t neuronsNum;
};

#endif
