#include "Knowledge.h"

const vector_size_t Knowledge::DEFAULT_INPUTS_NUM = 100;
const vector_size_t Knowledge::DEFAULT_OUTPUTS_NUM = 1;

Knowledge::Knowledge() {
    this->inputsNum = DEFAULT_INPUTS_NUM;
    this->outputsNum = DEFAULT_OUTPUTS_NUM;
    this->experiences = new Vector<Experience>();
}

Knowledge::Knowledge(vector_size_t inputsNum, vector_size_t outputsNum) {
    this->inputsNum = inputsNum;
    this->outputsNum = outputsNum;
    this->experiences = new Vector<Experience>();
}

void Knowledge::addOne(Experience* newExperience) {
    this->experiences->addLast(newExperience);
}

vector_size_t Knowledge::getInputsNum() {
    return this->inputsNum;
}

vector_size_t Knowledge::getOutputsNum() {
    return this->outputsNum;
}

Experience* Knowledge::getExperiences() {
    return this->experiences->getItems();
}

Vector<Experience>* Knowledge::getExperiencesVector() {
    return this->experiences;
}
