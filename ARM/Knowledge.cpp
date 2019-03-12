#include "Knowledge.h"

void Knowledge::describe() {
    //TODO
}

uint16_t Knowledge::getInputsNum() {
    return this->inputsNum;
}

uint16_t Knowledge::getOutputsNum() {
    return this->outputsNum;
}

double** Knowledge::getInputs() {
    return this->inputs;
}

double** Knowledge::getOutputs() {
    return this->outputs;
 }

void Knowledge::setInputsNum(uint16_t num) {
    this->inputsNum = num;
}

void Knowledge::setOutputsNum(uint16_t num) {
    this->outputsNum = num;
}

void Knowledge::setInputs(double** inputs) {
    this->inputs = inputs;
}

void Knowledge::setOutputs(double** outputs) {
    this->outputs = outputs;
}
