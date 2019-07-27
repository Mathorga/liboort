#include "Perceptron.h"

namespace Oort {
    const neuron_value_t Perceptron::DEFAULT_VALUE = 0.5;
    const perceptron_error_t Perceptron::DEFAULT_ERROR = 0.0;

    Perceptron::Perceptron(vector_size_t id) {
        // TODO Implement real constructor.
        this->id = id;
        this->value = DEFAULT_VALUE;
        this->error = DEFAULT_ERROR;
        this->synapses = new Vector<PerceptronSynapse>();
    }

    Perceptron::Perceptron(vector_size_t id, Neuron::NeuronType type) : Perceptron(id) {
        this->type = type;
    }

    Perceptron::Perceptron(vector_size_t id, neuron_value_t value) : Perceptron(id) {
        this->value = value;
    }

    Perceptron::Perceptron(vector_size_t id, neuron_value_t value, Neuron::NeuronType type) : Perceptron(id, value) {
        this->type = type;
    }

    Perceptron::Perceptron(vector_size_t id, neuron_value_t value, vector_size_t synapsesNum) : Perceptron(id, value) {
        for (vector_size_t i = 0; i < synapsesNum; i++) {
            this->synapses->addLast(new PerceptronSynapse(PerceptronSynapse::DEFAULT_WEIGHT));
        }
    }

    Perceptron::Perceptron(Perceptron& other) {
        this->id = other.getId();
        this->value = other.getValue();
        this->synapses = other.getSynapses();
    }

    void Perceptron::print() {
        setPrintColor(ANSI_COLOR_CYAN);
        printf("\t|PERCEPTRON\n");
        printf("\t|Id %d\n", this->id);
        printf("\t|Type %d\n", this->type);
        printf("\t|Value %f\n", this->value);
        printf("\t|Error %f\n", this->error);
        setPrintColor(ANSI_COLOR_RESET);
        for (vector_size_t i = 0; i < this->synapses->getSize(); i++) {
            this->synapses->getItem(i)->print();
        }
        printf("\n");
    }

    vector_size_t Perceptron::getId() {
        return this->id;
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

    PerceptronSynapse* Perceptron::getSynapse(vector_size_t index) {
        return this->synapses->getItem(index);
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
}
