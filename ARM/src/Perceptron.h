#ifndef __PERCEPTRON__
#define __PERCEPTRON__

#include "Neuron.h"
#include "Synapse.h"

#define neuron_error_t uint16_t
#define synapses_num_t uint16_t

class Perceptron : public Neuron {
public:
    // Constructors.
    Perceptron();

    // Getters.
    float getFloatValue();
    synapses_num_t getSynapsesNum();

    // Setters.
    void setDValue(neuron_value_t dValue);

private:
    NeuronType type;
    neuron_value_t dValue;
    neuron_error_t error;
    neuron_error_t delta;
    neuron_error_t partialDelta;

    synapses_num_t synapsesNum;
    Synapse** inputs;
};

#endif
