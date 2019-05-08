#include "Perceptron.h"

Perceptron::Perceptron() {
    // TODO Implement real constructor.
    this->value = 0;
    this->synapses = new Vector<PerceptronSynapse>();
}

Perceptron::Perceptron(neuron_value_t value) {
    this->value = value;
    this->synapses = new Vector<PerceptronSynapse>();
}

Perceptron::Perceptron(neuron_value_t value, vector_size_t synapsesNum) {
    this->value = value;
    this->synapses = new Vector<PerceptronSynapse>(synapsesNum);
    for (vector_size_t i = 0; i < synapsesNum; i++) {
        this->synapses->addLast(new PerceptronSynapse(PerceptronSynapse::defaultWeight));
    }
}

Perceptron::Perceptron(Neuron& neuron) {
    this->value = neuron.getValue();
    this->synapses = new Vector<PerceptronSynapse>();
}

void Perceptron::print() {
    printf("----------PERCEPTRON----------\n");
    printf("Value %f\n", this->value);
    for (vector_size_t i = 0; i < this->synapses->getSize(); i++) {
        this->synapses->getItems()[i].print();
    }
}

neuron_value_t Perceptron::getDValue() {
    return this->dValue;
}

perceptron_error_t Perceptron::getError() {
    return this->error;
}

neuron_value_t Perceptron::getExpectedOutput() {
    return this->expectedOutput;
}

vector_size_t Perceptron::getSynapsesNum() {
    return this->synapses->getSize();
}

Vector<PerceptronSynapse>* Perceptron::getSynapses() {
    return this->synapses;
}

Perceptron** Perceptron::getInputs() {
    //TODO Return neurons connected to this via synapses.
}

// Setters.
void Perceptron::setDValue(neuron_value_t dValue) {
    this->dValue = dValue;
}

void Perceptron::setError(perceptron_error_t error) {
    this->error = error;
}

void Perceptron::addError(perceptron_error_t error) {
    this->error += error;
}

void Perceptron::setExpectedOutput(neuron_value_t expectedOutput) {
    this->expectedOutput = expectedOutput;
}
