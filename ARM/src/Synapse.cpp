#include "Synapse.h"

Synapse::Synapse() {
    this->weight = 0;
}

Synapse::Synapse(Neuron* inputNeuron, Neuron* outputNeuron) {
    this->inputNeuron = inputNeuron;
    this->outputNeuron = outputNeuron;
    this->weight = 0;
}

Neuron* getInputNeuron() {
    return this->inputNeuron;
}

// Neuron* getOutputNeuron() {
//     return this->outputNeuron;
// }

synapse_weight_t getWeight() {
    return this->weight;
}
