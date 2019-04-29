#ifndef __PERCEPTRON__
#define __PERCEPTRON__

#include "Neuron.h"
#include "Synapse.h"

#define neuron_error_t uint16_t

class Perceptron : public Neuron {
public:
    // Constructors.
    Perceptron();

    float getFloatValue();

private:
    NeuronType type;
    neuron_value_t dValue;
    neuron_error_t error;
    neuron_error_t delta;
    neuron_error_t partialDelta;

    //TODO Manage using synapses.
    Perceptron** inputs;
};

#endif
