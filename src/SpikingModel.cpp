#include "SpikingModel.h"

namespace Oort {
    SpikingModel::SpikingModel() {
        this->inputsNum = 1;
        this->hiddensNum = 0;
        this->outputsNum = 1;
        this->neuronsNum = this->inputsNum + this->hiddensNum + this->outputsNum;
        this->neurons = new SpikingNeuron[this->neuronsNum];//(SpikingNeuron*) malloc(this->neuronsNum * sizeof(SpikingNeuron));
        for (uint32_t i = 0; i < this->neuronsNum; i++) {
            this->neurons[i].setValue(i);//*(new SpikingNeuron((NEURON_VALUE_T) 10));
        }
    }

    void SpikingModel::print() {
        for (uint32_t i = 0; i < this->neuronsNum; i++) {
            printf("\nvalue %d\n", this->neurons[i].getValue());
        }
    }
}
