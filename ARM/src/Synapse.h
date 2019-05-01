#ifndef __SYNAPSE__
#define __SYNAPSE__

#include "Neuron.h"
#include "utils.h"

#define synapse_weight_t uint16_t

class Synapse {
public:
    // Constructors.
    // Synapse();
    // Synapse(Neuron* inputNeuron);

    // Getters.
    // Neuron* getInputNeuron();
    // Neuron* getOutputNeuron();
    synapse_weight_t getWeight();

    // Setters.
    void setWeight(synapse_weight_t weight);
    // void setInputNeuron(Neuron* inputNeuron);

protected:
    // Neuron* inputNeuron;
    // Neuron* outputNeuron;
    synapse_weight_t weight;
};

#endif
