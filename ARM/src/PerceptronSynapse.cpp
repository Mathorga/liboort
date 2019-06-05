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
    printf("|------------------SYNAPSE----------\t\t|\n");
    printf("|\tInput %d\t\t\t\t\t|\n", this->inputNeuron->getId());
    printf("|\tWeight %f\t\t\t\t|\n", this->weight);
}

Perceptron* PerceptronSynapse::getInputNeuron() {
    return this->inputNeuron;
}
