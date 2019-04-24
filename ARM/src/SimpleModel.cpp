#include "SimpleModel.h"

void SimpleModel::describe() {
    printf("\n---------------------------------SimpleModel---------------------------------\n");
    for (uint16_t i = 0; i < this->neuronsNum; i++) {
        if (this->neurons[i].type == SimpleModel::typeOutput) {
            setPrintColor(ANSI_COLOR_YELLOW);
        } else if (this->neurons[i].type == SimpleModel::typeInput) {
            setPrintColor(ANSI_COLOR_CYAN);
        }
        printf("Neuron %d: type %d\t\t\tvalue %.5f\tenabled %d\n", i, this->neurons[i].type, this->neurons[i].value, this->neurons[i].enabled);
        if (this->neurons[i].type == SimpleModel::typeOutput || this->neurons[i].type == SimpleModel::typeInput) {
            setPrintColor(ANSI_COLOR_RESET);
        }
    }
    for (uint16_t i = 0; i < this->synapsesNum; i++) {
        if (!this->synapses[i].enabled) {
            setPrintColor(ANSI_COLOR_GREY);
        }
        printf("Synapse %d: input %d\toutput %d\tweight %.5f\tenabled %d\n", i, this->synapses[i].inputNeuron, this->synapses[i].outputNeuron, this->synapses[i].weight, this->synapses[i].enabled);
        if (!this->synapses[i].enabled) {
            setPrintColor(ANSI_COLOR_RESET);
        }
    }
    printf("-----------------------------------------------------------------------\n");
    return;
}

void SimpleModel::randomizeInputValues() {
    // Generate random seed.
    srand(time(NULL));

    for (uint16_t i = 0; i < this->inputNum; i++) {
        this->neurons[i].value = dRandBetween(0, 1);
        // printf("\n%f\n", this->neurons[i].value);
    }
}

void SimpleModel::randomizeSynapsesWeights() {
    // Generate random seed.
    srand(time(NULL));

    for (uint16_t i = 0; i < this->synapsesNum; i++) {
        this->synapses[i].weight = dRandBetween(-1, 1);
    }
}

uint16_t SimpleModel::getInputNum() {
    return this->inputNum;
}

uint16_t SimpleModel::getOutputNum() {
    return this->outputNum;
}

uint16_t SimpleModel::getHiddenNum() {
    return this->hiddenNum;
}

uint16_t SimpleModel::getNeuronsNum() {
    return this->neuronsNum;
}

uint16_t SimpleModel::getSynapsesNum() {
    return this->synapsesNum;
}

SimpleModel::_Neuron *SimpleModel::getNeurons() {
    return this->neurons;
}

SimpleModel::_Synapse *SimpleModel::getSynapses() {
    return this->synapses;
}

void SimpleModel::setInputNum(uint16_t num) {
    this->inputNum = num;
}

void SimpleModel::setOutputNum(uint16_t num) {
    this->outputNum = num;
}

void SimpleModel::setHiddenNum(uint16_t num) {
    this->hiddenNum = num;
}

void SimpleModel::setNeuronsNum(uint16_t num) {
    this->neuronsNum = num;
}

void SimpleModel::setSynapsesNum(uint16_t num) {
    this->synapsesNum = num;
}

void SimpleModel::setNeurons(_Neuron *inputNeurons) {
    this->neurons = inputNeurons;
}

void SimpleModel::setSynapses(_Synapse *inputSynapses) {
    this->synapses = inputSynapses;
}
