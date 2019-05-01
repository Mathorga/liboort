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

    // Getters.
    neuron_value_t getValue();
    NeuronType getType();

    // Setters.
    void setValue(neuron_value_t value);
    void setType(NeuronType type);

protected:
    NeuronType type;
    neuron_value_t value;
};

#endif
