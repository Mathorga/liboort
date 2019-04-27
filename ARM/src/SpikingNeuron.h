#ifndef __SPIKING_NEURON__
#define __SPIKING_NEURON__

#include "Neuron.h"

class SpikingNeuron : public Neuron {
public:
    // Constructors.
    SpikingNeuron();
    SpikingNeuron(NEURON_VALUE_T value);

private:
    NeuronType type;
    bool state;
    bool outState;
    SpikingNeuron** inputs;
};

#endif
