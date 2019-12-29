#include "Perceptron.h"

namespace Oort {
    const neuron_value_t Perceptron::DEFAULT_VALUE = 0.5;
    const perceptron_error_t Perceptron::DEFAULT_ERROR = 0.0;
    const neuron_value_t Perceptron::DEFAULT_BIAS = 1.0;

    Perceptron::Perceptron() {}

    Perceptron::Perceptron(vector_size_t id) {
        // TODO Implement real constructor.
        this->id = id;
        this->value = DEFAULT_VALUE;
        this->error = DEFAULT_ERROR;
        this->synapses = new Vector<PerceptronSynapse>();
        this->bias = DEFAULT_BIAS;
        // this->gradient = 0.0;
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
            this->synapses->addLast(new PerceptronSynapse(/*PerceptronSynapse::DEFAULT_WEIGHT*/));
        }
    }

    Perceptron::Perceptron(Perceptron& other) {
        this->id = other.getId();
        this->value = other.getValue();
        this->synapses = other.getSynapses();
    }

    void Perceptron::print() {
        setPrintColor(ANSI_COLOR_CYAN);
        printf("\t|---------PERCEPTRON---------\n");
        printf("\t|Id %d\n", this->id);
        printf("\t|Type %d\n", this->type);
        printf("\t|Value %f\n", this->value);
        // printf("\t|DValue %f\n", this->dValue);
        // printf("\t|DOutput %f\n", this->dOutput);
        // printf("\t|DInput %f\n", this->dInput);
        // printf("\t|Error %f\n", this->error);
        setPrintColor(ANSI_COLOR_RESET);
        for (vector_size_t i = 0; i < this->synapses->getSize(); i++) {
            this->synapses->getItem(i)->print();
        }
    }

    vector_size_t Perceptron::getId() {
        return this->id;
    }

    neuron_value_t Perceptron::getDValue() {
        return this->dValue;
    }

    neuron_value_t Perceptron::getDInput() {
        return this->dInput;
    }

    neuron_value_t Perceptron::getDOutput() {
        return this->dOutput;
    }

    perceptron_error_t Perceptron::getError() {
        return this->error;
    }

    neuron_value_t Perceptron::getBias() {
        return this->bias;
    }

    // neuron_value_t Perceptron::getGradient() {
    //     return this->gradient;
    // }

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
        return nullptr;
    }

    Perceptron Perceptron::getNullPerceptron() {
        Perceptron nullPerceptron(-1);
        return nullPerceptron;
    }

    // Setters.
    void Perceptron::setDValue(neuron_value_t dValue) {
        this->dValue = dValue;
    }

    void Perceptron::setDInput(neuron_value_t dInput) {
        this->dInput = dInput;
    }

    void Perceptron::setDOutput(neuron_value_t dOutput) {
        this->dOutput = dOutput;
    }

    void Perceptron::addDOutput(neuron_value_t dOutput) {
        this->dOutput += dOutput;
    }

    void Perceptron::setError(perceptron_error_t error) {
        this->error = error;
    }

    void Perceptron::setBias(neuron_value_t bias) {
        this->bias = bias;
    }

    // void Perceptron::setGradient(neuron_value_t gradient) {
    //     this->gradient = gradient;
    // }

    void Perceptron::addError(perceptron_error_t error) {
        this->error += error;
    }

    void Perceptron::setExpectedOutput(neuron_value_t expectedOutput) {
        this->expectedOutput = expectedOutput;
    }
}
