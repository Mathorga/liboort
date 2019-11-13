#include "Experience.h"

namespace Oort {
    Experience::Experience() {
        this->inputs = new Vector<neuron_value_t>();
        this->outputs = new Vector<neuron_value_t>();
    }

    Experience::Experience(vector_size_t inputsNum, vector_size_t outputsNum) {
        this->inputs = new Vector<neuron_value_t>(inputsNum);
        this->outputs = new Vector<neuron_value_t>(outputsNum);
    }

    Experience::Experience(vector_size_t inputsNum, neuron_value_t* inputValues, vector_size_t outputsNum, neuron_value_t* outputValues) {
        this->inputs = new Vector<neuron_value_t>(inputsNum, inputValues);
        this->outputs = new Vector<neuron_value_t>(outputsNum, outputValues);
    }

    Experience::Experience(Vector<neuron_value_t>* inputs, Vector<neuron_value_t>* outputs) {
        this->inputs = inputs;
        this->outputs = outputs;
    }

    void Experience::print() {
        printf("\nExperience\n");
        for (vector_size_t i = 0; i < this->inputs->getSize(); i++) {
            printf("%f ", *(this->inputs->getItem(i)));
        }
        printf("\t");
        for (vector_size_t i = 0; i < this->outputs->getSize(); i++) {
            printf("%f ", *(this->outputs->getItem(i)));
        }
        printf("\n\n");
    }

    neuron_value_t Experience::getInput(vector_size_t index) {
        return *(this->inputs->getItem(index));
    }

    neuron_value_t Experience::getOutput(vector_size_t index) {
        return *(this->outputs->getItem(index));
    }

    neuron_value_t* Experience::getInputs() {
        return this->inputs->getItems();
    }

    neuron_value_t* Experience::getOutputs() {
        return this->outputs->getItems();
    }

    vector_size_t Experience::getInputsNum() {
        return this->inputs->getSize();
    }

    vector_size_t Experience::getOutputsNum() {
        return this->outputs->getSize();
    }

    void Experience::setInputs(neuron_value_t* inputs, vector_size_t inputsNum) {
        this->inputs->setItems(inputs, inputsNum);
    }

    void Experience::setInputs(Vector<neuron_value_t>* inputs) {
        this->inputs = inputs;
    }

    void Experience::setOutputs(neuron_value_t* outputs, vector_size_t outputsNum) {
        this->outputs->setItems(outputs, outputsNum);
    }

    void Experience::setOutputs(Vector<neuron_value_t>* outputs) {
        this->outputs = outputs;
    }
}
