#include "Knowledge.h"

namespace Oort {
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

    void Knowledge::addExperience(Experience* experience) {
        if (experience->getInputsNum() == this->inputsNum && experience->getOutputsNum() == this->outputsNum) {
            this->experiences->addLast(experience);
        } else {
            printf("\nmyIns %d, myOuts %d, expIns %d, expOuts %d\n", this->inputsNum, this->outputsNum, experience->getInputsNum(), experience->getOutputsNum());
            printf("\n<Knowledge.addExperience()> Error adding experience: Inconsistent size\n");
        }
    }

    void Knowledge::addExperiences(Experience* experiences, vector_size_t size) {
        vector_size_t errorsNum = 0;

        for (vector_size_t i = 0; i < size; i++) {
            if (experiences[i].getInputsNum() == this->inputsNum && experiences[i].getOutputsNum() == this->outputsNum) {
                this->experiences->addLast(&(experiences[i]));
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

    Experience* Knowledge::getExperience(vector_size_t index) {
        return this->experiences->getItem(index);
    }

    Experience* Knowledge::getExperiences() {
        return this->experiences->getItems();
    }

    Vector<Experience>* Knowledge::getExperiencesVector() {
        return this->experiences;
    }

    vector_size_t Knowledge::getExperiencesNum() {
        return this->experiences->getSize();
    }
}
