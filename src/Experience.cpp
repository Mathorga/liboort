#include "Experience.h"

namespace oort {
    Experience::Experience(tensor::dtensor1d inputs, tensor::dtensor1d outputs) {
        this->inputs = inputs;
        this->outputs = outputs;
    }

    Experience::Experience(uint32_t inputsNum, uint32_t outputsNum) {
        tensor::alloc(&(this->inputs), inputsNum);
        tensor::alloc(&(this->outputs), outputsNum);
    }

    Experience::Experience() : Experience(0, 0) {}

    void Experience::print() {
        printf("\nExperience\n");
        for (uint32_t i = 0; i < this->inputs.width; i++) {
            printf("%f ", this->inputs.values[i]);
        }
        printf("    ");
        for (uint32_t i = 0; i < this->outputs.width; i++) {
            printf("%f ", this->outputs.values[i]);
        }
        printf("\n");
    }

    double Experience::getInput(uint32_t index) {
        return this->inputs.values[index];
    }

    double Experience::getOutput(uint32_t index) {
        return this->outputs.values[index];
    }

    tensor::dtensor1d Experience::getInputs() {
        return this->inputs;
    }

    tensor::dtensor1d Experience::getOutputs() {
        return this->outputs;
    }

    uint32_t Experience::getInputsNum() {
        return this->inputs.width;
    }

    uint32_t Experience::getOutputsNum() {
        return this->outputs.width;
    }

    void Experience::setInputs(tensor::dtensor1d inputs) {
        this->inputs = inputs;
    }

    void Experience::setOutputs(tensor::dtensor1d outputs) {
        this->outputs = outputs;
    }
}
