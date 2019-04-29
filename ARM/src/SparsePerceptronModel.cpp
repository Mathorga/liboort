#include "SparsePerceptronModel.h"

SparsePerceptronModel::SparsePerceptronModel() {
    this->inputsNum = 1;
    this->hiddensNum = 0;
    this->outputsNum = 1;
    this->neuronsNum = this->inputsNum + this->hiddensNum + this->outputsNum;
    this->neurons = new Perceptron[this->neuronsNum];
    for (uint32_t i = 0; i < this->neuronsNum; i++) {
        this->neurons[i].setValue(i);//*(new SpikingNeuron((NEURON_VALUE_T) 10));
    }
}

void SparsePerceptronModel::print() {
    printf("\nSparsePerceptronModel\n");
}
