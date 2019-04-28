#include "Model.h"

neurons_num_t Model::getInputsNum() {
    return this->inputsNum;
}

neurons_num_t Model::getOutputsNum() {
    return this->outputsNum;
}

neurons_num_t Model::getHiddensNum() {
    return this->hiddensNum;
}

neurons_num_t Model::getNeuronsNum() {
    return this->neuronsNum;
}

Neuron* Model::getNeurons() {
    return this->neurons;
}
