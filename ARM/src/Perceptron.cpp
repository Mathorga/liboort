#include "Perceptron.h"

Perceptron::Perceptron() {
    // TODO Implement real constructor.
    this->value = 0;
}

Perceptron::Perceptron(Neuron& neuron) {
    this->value = neuron.getValue();
}

float Perceptron::getFloatValue() {
    //TODO Convert this->value to float (0,1).
    return 0.0;
}

neuron_error_t Perceptron::getError() {
    return this->error;
}

neuron_value_t Perceptron::getExpectedOutput() {
    return this->expectedOutput;
}

synapses_num_t Perceptron::getSynapsesNum() {
    return this->synapsesNum;
}

PerceptronSynapse** Perceptron::getSynapses() {
    return this->synapses;
}

Perceptron** Perceptron::getInputs() {
    //TODO Return neurons connected to this via synapses.
}

// Setters.
void Perceptron::setDValue(neuron_value_t dValue) {
    this->dValue = dValue;
}

void Perceptron::setError(neuron_error_t error) {
    this->error = error;
}

void Perceptron::addError(neuron_error_t error) {
    this->error += error;
}

void Perceptron::setExpectedOutput(neuron_value_t expectedOutput) {
    this->expectedOutput = expectedOutput;
}
