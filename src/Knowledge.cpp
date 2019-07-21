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

void Knowledge::addExperience(Experience* newExperience) {
    if (newExperience->getInputsNum() == this->inputsNum && newExperience->getOutputsNum() == this->outputsNum) {
        this->experiences->addLast(newExperience);
    } else {
        printf("\n<Knowledge.addExperience()> Error adding experience: Inconsistent size\n");
    }
}

void Knowledge::addExperiences(Experience* newExperiences, vector_size_t size) {
    vector_size_t errorsNum = 0;

    for (vector_size_t i = 0; i < size; i++) {
        if (newExperiences[i].getInputsNum() == this->inputsNum && newExperiences[i].getOutputsNum() == this->outputsNum) {
            this->experiences->addLast(&(newExperiences[i]));
        } else {
            errorsNum++;
        }
    }
    if (errorsNum > 0) {
        printf("\n<Knowledge.addExperiences()> Error adding %d experiences: Inconsistent sizes\n", errorsNum);
    }
}

void Knowledge::print() {
    printf("\nKnowledge - Inputs %d Outputs %d\n", this->inputsNum, this->outputsNum);

    // Print all experiences.
    for (vector_size_t i = 0; i < this->experiences->getSize(); i++) {
        this->experiences->getItem(i)->print();
    }
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
