#include "Model.h"

void Model::computeNeuronsNum() {
    this->neuronsNum = this->inputsNum + this->outputsNum + this->hiddensNum;
}

vector_size_t Model::getInputsNum() {
    return this->inputsNum;
}

vector_size_t Model::getOutputsNum() {
    return this->outputsNum;
}

vector_size_t Model::getHiddensNum() {
    return this->hiddensNum;
}

vector_size_t Model::getNeuronsNum() {
    return this->neuronsNum;
}

// Neuron* Model::getNeurons() {
//     return this->neurons;
// }

void Model::setInputsNum(vector_size_t inputsNum) {
    this->inputsNum = inputsNum;
}

void Model::setOutputsNum(vector_size_t outputsNum) {
    this->outputsNum = outputsNum;
}

void Model::setHiddensNum(vector_size_t hiddensNum) {
    this->hiddensNum = hiddensNum;
}

void Model::setNeuronsNum(vector_size_t neuronsNum) {
    this->neuronsNum = neuronsNum;
}
