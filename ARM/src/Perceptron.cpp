#include "Perceptron.h"

const neuron_value_t Perceptron::DEFAULT_VALUE = 0.5;

Perceptron::Perceptron(neurons_num_t id) {
    // TODO Implement real constructor.
    this->id = id;
    this->value = DEFAULT_VALUE;
    this->synapses = new Vector<PerceptronSynapse>();
}

Perceptron::Perceptron(neurons_num_t id, neuron_value_t value) : Perceptron(id) {
    this->value = value;
}

Perceptron::Perceptron(neurons_num_t id, neuron_value_t value, Neuron::NeuronType type) : Perceptron(id, value) {
    this->type = type;
}

Perceptron::Perceptron(neurons_num_t id, neuron_value_t value, vector_size_t synapsesNum) : Perceptron(id, value) {
    for (vector_size_t i = 0; i < synapsesNum; i++) {
        this->synapses->addLast(new PerceptronSynapse(PerceptronSynapse::defaultWeight));
    }
}

Perceptron::Perceptron(Neuron& neuron) {
    this->id = neuron.getId();
    this->value = neuron.getValue();
    this->synapses = new Vector<PerceptronSynapse>();
}

void Perceptron::print() {
    printf("|----------PERCEPTRON----------\t\t\t|\n");
    printf("|Value %f\t\t\t\t\t|\n", this->value);
    for (vector_size_t i = 0; i < this->synapses->getSize(); i++) {
        this->synapses->getItem(i)->print();
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

Perceptron Perceptron::getNullPerceptron() {
    Perceptron nullPerceptron(-1);
    return nullPerceptron;
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
