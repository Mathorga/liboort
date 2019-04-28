#ifndef __SYNAPSE__
#define __SYNAPSE__

#include "Neuron.h"
#include "utils.h"

#define synapse_weight_t uint16_t

class Synapse {
public:
    // Constructors.
    Synapse();
    Synapse(Neuron* inputNeuron, Neuron* outputNeuron);

    // Getters.
    Neuron* getInputNeuron();
    Neuron* getOutputNeuron();
    synapse_weight_t getWeight();

    // Setters.
    void setInputNeuron(Neuron* inputNeuron);
    void setOutputNeuron(Neuron* outputNeuron);

private:
    Neuron* inputNeuron;
    Neuron* outputNeuron;
    synapse_weight_t weight;
};

#endif
