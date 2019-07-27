#ifndef __SPIKING_NEURON__
#define __SPIKING_NEURON__

#include "Neuron.h"

namespace Oort {
    class SpikingNeuron : public Neuron {
    public:
        // Constructors.
        SpikingNeuron();
        SpikingNeuron(neuron_value_t value);

    private:
        NeuronType type;
        bool state;
        bool outState;
        SpikingNeuron** inputs;
    };
}

#endif
