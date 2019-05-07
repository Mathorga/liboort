#include "SparsePerceptronModel.h"

SparsePerceptronModel::SparsePerceptronModel() {
    this->inputsNum = 1;
    this->hiddensNum = 0;
    this->outputsNum = 1;
    this->neuronsNum = this->inputsNum + this->hiddensNum + this->outputsNum;
    this->items = new Perceptron[this->neuronsNum];
    for (neurons_num_t i = 0; i < this->neuronsNum; i++) {
        this->items[i].setValue(0.5);//*(new SpikingNeuron((NEURON_VALUE_T) 10));
    }
}

SparsePerceptronModel::SparsePerceptronModel(neurons_num_t inputsNum, neurons_num_t outputsNum, bool createSynapses) {
    this->inputsNum = inputsNum;
    this->hiddensNum = 0;
    this->outputsNum = outputsNum;
    this->neuronsNum = this->inputsNum + this->hiddensNum + this->outputsNum;
    this->size = this->inputsNum + this->hiddensNum + this->outputsNum;

    // Create neurons.
    this->items = new Perceptron[this->neuronsNum];
    for (neurons_num_t i = 0; i < this->neuronsNum; i++) {
        this->items[i].setValue(i);
        this->items[i].setType(i < inputsNum ? Neuron::typeInput : Neuron::typeOutput);
    }

    if (createSynapses) {
        // Create synapses.
        for (neurons_num_t i = this->inputsNum; i < this->neuronsNum; i++) {
            for (neurons_num_t j = 0; j < this->inputsNum; j++) {
                this->items[i].getSynapses()->addLast(new PerceptronSynapse(&(this->items[j]), PerceptronSynapse::defaultWeight));
            }
        }
    }
}

void SparsePerceptronModel::print() {
    printf("\n-----------SparsePerceptronModel-----------");
    printf("\nSize %d\n", this->size);

    for (vector_size_t i = 0; i < this->size; i++) {
        this->items[i].print();
    }
}

Perceptron* SparsePerceptronModel::getNeurons() {
    return this->items;
}
