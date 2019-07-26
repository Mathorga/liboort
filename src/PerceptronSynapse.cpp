#include "PerceptronSynapse.h"

const synapse_weight_t PerceptronSynapse::DEFAULT_WEIGHT = 0.001;

PerceptronSynapse::PerceptronSynapse() {
    this->weight = DEFAULT_WEIGHT;
    this->inputNeuron = NULL;
}

PerceptronSynapse::PerceptronSynapse(synapse_weight_t weight) {
    this->weight = weight;
    this->inputNeuron = NULL;
}

PerceptronSynapse::PerceptronSynapse(Perceptron* inputNeuron) {
    this->weight = DEFAULT_WEIGHT;
    this->inputNeuron = inputNeuron;
}

PerceptronSynapse::PerceptronSynapse(Perceptron* inputNeuron, synapse_weight_t weight) {
    this->weight = weight;
    this->inputNeuron = inputNeuron;
}

void PerceptronSynapse::print() {
    setPrintColor(ANSI_COLOR_YELLOW);
    printf("\t\t|SYNAPSE\n");
    printf("\t\t|Input %d\n", this->inputNeuron->getId());
    printf("\t\t|Weight %f\n", this->weight);
    setPrintColor(ANSI_COLOR_RESET);
}

Perceptron* PerceptronSynapse::getInputNeuron() {
    return this->inputNeuron;
}

vector_size_t PerceptronSynapse::getInputId() {
    return this->inputNeuron->getId();
}
