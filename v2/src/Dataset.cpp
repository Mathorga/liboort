#include "Dataset.h"

namespace Oort {
    const vector_size_t Dataset::DEFAULT_INPUTS_NUM = 100;
    const vector_size_t Dataset::DEFAULT_OUTPUTS_NUM = 1;

    Dataset::Dataset() {
        this->inputsNum = DEFAULT_INPUTS_NUM;
        this->outputsNum = DEFAULT_OUTPUTS_NUM;
        this->experiences = new Vector<Experience>();
    }

    Dataset::Dataset(vector_size_t inputsNum, vector_size_t outputsNum) {
        this->inputsNum = inputsNum;
        this->outputsNum = outputsNum;
        this->experiences = new Vector<Experience>();
    }

    void Dataset::addExperience(Experience* experience) {
        // Check if inputs and outputs numbers of the experience match those of the Dataset.
        // Print an error in case of inconsistency.
        if (experience->getInputsNum() == this->inputsNum && experience->getOutputsNum() == this->outputsNum) {
            this->experiences->addLast(*experience);
        } else {
            printf("\nmyIns %d, myOuts %d, expIns %d, expOuts %d\n", this->inputsNum, this->outputsNum, experience->getInputsNum(), experience->getOutputsNum());
            printf("\n<Dataset.addExperience()> Error adding experience: Inconsistent size\n");
        }
    }

    void Dataset::addExperiences(Experience* experiences, vector_size_t size) {
        vector_size_t errorsNum = 0;

        for (vector_size_t i = 0; i < size; i++) {
            if (experiences[i].getInputsNum() == this->inputsNum && experiences[i].getOutputsNum() == this->outputsNum) {
                this->experiences->addLast(&(experiences[i]));
            } else {
                errorsNum++;
            }
        }
        if (errorsNum > 0) {
            printf("\n<Dataset.addExperiences()> Error adding %d experiences: Inconsistent sizes\n", errorsNum);
        }
    }

    void Dataset::print() {
        printf("\nDataset - Inputs %d Outputs %d\n", this->inputsNum, this->outputsNum);

        // Print all experiences.
        for (vector_size_t i = 0; i < this->experiences->getSize(); i++) {
            this->experiences->getItem(i)->print();
        }
    }

    vector_size_t Dataset::getInputsNum() {
        return this->inputsNum;
    }

    vector_size_t Dataset::getOutputsNum() {
        return this->outputsNum;
    }

    Experience* Dataset::getExperience(vector_size_t index) {
        return this->experiences->getItem(index);
    }

    Experience* Dataset::getExperiences() {
        return this->experiences->getItems();
    }

    Vector<Experience>* Dataset::getExperiencesVector() {
        return this->experiences;
    }

    vector_size_t Dataset::getExperiencesNum() {
        return this->experiences->getSize();
    }
}
