#include "Synapse.h"

// Synapse::Synapse() {
//     this->weight = 0;
// }
//
// Synapse::Synapse(Neuron* inputNeuron) {
//     this->inputNeuron = inputNeuron;
//     this->weight = 0;
// }
//
// Neuron* Synapse::getInputNeuron() {
//     return this->inputNeuron;
// }
//
// Neuron* getOutputNeuron() {
//     return this->outputNeuron;
// }

synapse_weight_t Synapse::getWeight() {
    return this->weight;
}

void Synapse::setWeight(synapse_weight_t weight) {
    this->weight = weight;
}

// void Synapse::setInputNeuron(Neuron* inputNeuron) {
//     this->inputNeuron = inputNeuron;
// }
