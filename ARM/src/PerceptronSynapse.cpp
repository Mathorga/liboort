#include "PerceptronSynapse.h"

PerceptronSynapse::PerceptronSynapse() {
    this->weight = 0;
    this->inputNeuron = NULL;
}

PerceptronSynapse::PerceptronSynapse(synapse_weight_t weight) {
    this->weight = weight;
    this->inputNeuron = NULL;
}

PerceptronSynapse::PerceptronSynapse(Perceptron* inputNeuron) {
    this->weight = 0;
    this->inputNeuron = inputNeuron;
}

Perceptron* PerceptronSynapse::getInputNeuron() {
    return this->inputNeuron;
}
