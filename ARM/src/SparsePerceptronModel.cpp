#include "SparsePerceptronModel.h"

SparsePerceptronModel::SparsePerceptronModel() {
    this->inputsNum = 1;
    this->hiddensNum = 0;
    this->outputsNum = 1;
    this->neuronsNum = this->inputsNum + this->hiddensNum + this->outputsNum;
    this->items = new Perceptron[this->neuronsNum];
    for (neurons_num_t i = 0; i < this->neuronsNum; i++) {
        this->items[i].setValue(i);//*(new SpikingNeuron((NEURON_VALUE_T) 10));
    }
}

SparsePerceptronModel::SparsePerceptronModel(neurons_num_t inputsNum, neurons_num_t outputsNum) {
    this->inputsNum = inputsNum;
    this->hiddensNum = 0;
    this->outputsNum = outputsNum;
    this->neuronsNum = this->inputsNum + this->hiddensNum + this->outputsNum;
    this->items = new Perceptron[this->neuronsNum];
    for (neurons_num_t i = 0; i < this->neuronsNum; i++) {
        this->items[i].setValue(i);
    }
}

void SparsePerceptronModel::print() {
    printf("\nSparsePerceptronModel\n");
}

Perceptron* SparsePerceptronModel::getNeurons() {
    return this->items;
}
