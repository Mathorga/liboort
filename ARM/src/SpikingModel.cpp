#include "SpikingModel.h"

SpikingModel::SpikingModel() {
    this->inputsNum = 1;
    this->hiddensNum = 0;
    this->outputsNum = 1;
    this->neuronsNum = this->inputsNum + this->hiddensNum + this->outputsNum;
    this->neurons = (SpikingNeuron*) malloc(this->neuronsNum * sizeof(SpikingNeuron));
    for (uint32_t i = 0; i < this->neuronsNum; i++) {
        this->neurons[i] = *(new SpikingNeuron((NEURON_VALUE_T) 10));
    }
}

void SpikingModel::print() {
    printf("\nWAVELENGTH\n");
}
