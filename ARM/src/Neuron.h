#ifndef __NEURON__
#define __NEURON__

#include "utils.h"

#define neuron_value_t float
#define neurons_num_t uint32_t

class Neuron {
public:
    // Definition of the neuron types.
    enum NeuronType {
        typeInput = 0,
        typeOutput = 1,
        typeHidden = 2
    };

    // Getters.
    neurons_num_t getId();
    NeuronType getType();
    neuron_value_t getValue();

    // Setters.
    void setType(NeuronType type);
    void setValue(neuron_value_t value);

protected:
    neurons_num_t id;
    NeuronType type;
    neuron_value_t value;
};

#endif
