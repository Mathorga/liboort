#include "Model.h"

void Model::computeNeuronsNum() {
    this->neuronsNum = this->inputsNum + this->outputsNum + this->hiddensNum;
}

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

// Neuron* Model::getNeurons() {
//     return this->neurons;
// }

void Model::setInputsNum(neurons_num_t inputsNum) {
    this->inputsNum = inputsNum;
}

void Model::setOutputsNum(neurons_num_t outputsNum) {
    this->outputsNum = outputsNum;
}

void Model::setHiddensNum(neurons_num_t hiddensNum) {
    this->hiddensNum = hiddensNum;
}

void Model::setNeuronsNum(neurons_num_t neuronsNum) {
    this->neuronsNum = neuronsNum;
}
