#ifndef __NEURON__
#define __NEURON__

#include "utils.h"

#define neuron_value_t uint16_t

class Neuron {
public:
    // Definition of the neuron types.
    enum NeuronType {
        typeInput = 0,
        typeOutput = 1,
        typeHidden = 2
    };

    neuron_value_t getValue();
    void setValue(neuron_value_t value);

protected:
    neuron_value_t value;
};

#endif
