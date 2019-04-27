#include "Model.h"

uint32_t Model::getInputsNum() {
    return this->inputsNum;
}

uint32_t Model::getOutputsNum() {
    return this->outputsNum;
}

uint32_t Model::getHiddensNum() {
    return this->hiddensNum;
}

uint32_t Model::getNeuronsNum() {
    return this->neuronsNum;
}

Neuron* Model::getNeurons() {
    return this->neurons;
}
