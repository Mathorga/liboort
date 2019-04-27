#ifndef __NEURON__
#define __NEURON__

#include "utils.h"

#define NEURON_VALUE_T uint16_t

class Neuron {
public:
    // Definition of the neuron types.
    enum NeuronType {
        typeInput = 0,
        typeOutput = 1,
        typeHidden = 2
    };

    NEURON_VALUE_T getValue();
    void setValue(NEURON_VALUE_T value);

protected:
    NEURON_VALUE_T value;
};

#endif
