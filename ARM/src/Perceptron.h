#ifndef __PERCEPTRON__
#define __PERCEPTRON__

#include "Neuron.h"
#include "Synapse.h"

class Perceptron : public Neuron {
public:
    // Constructors.
    Perceptron();

    float getFloatValue();

private:
    NeuronType type;
    float value;
    float dValue;
    float error;
    float delta;
    float partialDelta;
    bool enabled;
    Perceptron** inputs;
};

#endif
