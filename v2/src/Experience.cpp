#include "Experience.h"

namespace Oort {
    Experience::Experience(dtensor1d inputs, dtensor1d outputs) {
        this->inputs = inputs;
        this->outputs = outputs;
    }

    Experience::Experience(uint32_t inputsNum, uint32_t outputsNum) {
        math::alloc(&(this->inputs), inputsNum);
        math::alloc(&(this->outputs), outputsNum);
    }

    Experience::Experience() : Experience(0, 0) {}

    void Experience::print() {
        printf("\nExperience\n");
        for (uint32_t i = 0; i < this->inputs->getSize(); i++) {
            printf("%f ", *(this->inputs->getItem(i)));
        }
        printf("\t");
        for (uint32_t i = 0; i < this->outputs->getSize(); i++) {
            printf("%f ", *(this->outputs->getItem(i)));
        }
        printf("\n\n");
    }

    double Experience::getInput(uint32_t index) {
        return *(this->inputs->getItem(index));
    }

    double Experience::getOutput(uint32_t index) {
        return *(this->outputs->getItem(index));
    }

    dtensor2d Experience::getInputs() {
        return this->inputs;
    }

    dtensor2d Experience::getOutputs() {
        return this->outputs;
    }

    uint32_t Experience::getInputsNum() {
        return this->inputs.width;
    }

    uint32_t Experience::getOutputsNum() {
        return this->outputs.width;
    }

    void Experience::setInputs(dtensor1d inputs) {
        this->inputs = inputs;
    }

    void Experience::setOutputs(dtensor1d outputs) {
        this->outputs = outputs;
    }
}
