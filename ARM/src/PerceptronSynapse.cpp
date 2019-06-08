#include "PerceptronSynapse.h"

synapse_weight_t PerceptronSynapse::defaultWeight = 0.5f;

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

PerceptronSynapse::PerceptronSynapse(Perceptron* inputNeuron, synapse_weight_t weight) {
    this->weight = weight;
    this->inputNeuron = inputNeuron;
}

void PerceptronSynapse::print() {
    printf("|------------------SYNAPSE----------\n");
    printf("|\tInput %d\n", this->inputNeuron->getId());
    printf("|\tWeight %f\n", this->weight);
}

Perceptron* PerceptronSynapse::getInputNeuron() {
    return this->inputNeuron;
}

neurons_num_t PerceptronSynapse::getInputId() {
    return this->inputNeuron->getId();
}
