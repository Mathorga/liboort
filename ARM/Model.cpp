#include "Model.h"

void Model::describe() {
    printf("\n---------------------------------Model---------------------------------\n");
    for (uint16_t i = 0; i < this->neuronsNum; i++) {
        if (this->neurons[i].type == Model::typeOutput) {
            setPrintColor(ANSI_COLOR_YELLOW);
        } else if (this->neurons[i].type == Model::typeInput) {
            setPrintColor(ANSI_COLOR_CYAN);
        }
        printf("Neuron %d: type %d\t\t\tvalue %.5f\tenabled %d\n", i, this->neurons[i].type, this->neurons[i].value, this->neurons[i].enabled);
        if (this->neurons[i].type == Model::typeOutput || this->neurons[i].type == Model::typeInput) {
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

void Model::randomizeInputValues() {
    // Generate random seed.
    srand(time(NULL));

    for (uint16_t i = 0; i < this->inputNum; i++) {
        this->neurons[i].value = dRandBetween(0, 1);
        // printf("\n%f\n", this->neurons[i].value);
    }
}

void Model::randomizeSynapsesWeights() {
    // Generate random seed.
    srand(time(NULL));

    for (uint16_t i = 0; i < this->synapsesNum; i++) {
        this->synapses[i].weight = dRandBetween(-1, 1);
    }
}

uint16_t Model::getInputNum() {
    return this->inputNum;
}

uint16_t Model::getOutputNum() {
    return this->outputNum;
}

uint16_t Model::getHiddenNum() {
    return this->hiddenNum;
}

uint16_t Model::getNeuronsNum() {
    return this->neuronsNum;
}

uint16_t Model::getSynapsesNum() {
    return this->synapsesNum;
}

Model::_Neuron *Model::getNeurons() {
    return this->neurons;
}

Model::_Synapse *Model::getSynapses() {
    return this->synapses;
}

void Model::setInputNum(uint16_t num) {
    this->inputNum = num;
}

void Model::setOutputNum(uint16_t num) {
    this->outputNum = num;
}

void Model::setHiddenNum(uint16_t num) {
    this->hiddenNum = num;
}

void Model::setNeuronsNum(uint16_t num) {
    this->neuronsNum = num;
}

void Model::setSynapsesNum(uint16_t num) {
    this->synapsesNum = num;
}

void Model::setNeurons(_Neuron *inputNeurons) {
    this->neurons = inputNeurons;
}

void Model::setSynapses(_Synapse *inputSynapses) {
    this->synapses = inputSynapses;
}
