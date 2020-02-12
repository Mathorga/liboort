#include "Knowledge.h"

namespace oort {
    const uint32_t Knowledge::DEFAULT_INPUTS_NUM = 100;
    const uint32_t Knowledge::DEFAULT_OUTPUTS_NUM = 1;

    Knowledge::Knowledge(uint32_t inputsNum, uint32_t outputsNum) {
        this->inputsNum = inputsNum;
        this->outputsNum = outputsNum;
        this->experiencesNum = 0;
    }

    Knowledge::Knowledge() : Knowledge(DEFAULT_INPUTS_NUM, DEFAULT_OUTPUTS_NUM) {}

    void Knowledge::addExperience(Experience* experience) {
        // Check if inputs and outputs numbers of the experience match those of the Knowledge.
        // Print an error in case of inconsistency.
        if (experience->getInputsNum() == this->inputsNum && experience->getOutputsNum() == this->outputsNum) {
            // Check if there's at least one experience, otherwise allocate
            // it.
            if (this->experiencesNum <= 0) {
                this->experiences = (Experience*) malloc(sizeof(Experience));
                this->experiences[0] = experience;
                this->experiencesNum++;
            } else {
                this->experiencesNum++;
                this->experiences = (Experience*) realloc(this->experiences, this->experiencesNum * sizeof(Experience));
            }
        } else {
            printf("\n<Knowledge.addExperience()> Error adding experience: Inconsistent size\n");
        }
    }

    void Knowledge::addExperiences(Experience* experiences, uint32_t size) {
        // Add all the given experiences.
        for (uint32_t i = 0; i < size; i++) {
            this->addExperience(experiences[i])
        }
    }

    void Knowledge::print() {
        printf("\nKnowledge - Inputs %d Outputs %d\n", this->inputsNum, this->outputsNum);

        // Print all experiences.
        for (uint32_t i = 0; i < this->experiences->getSize(); i++) {
            this->experiences[i]->print();
        }
    }

    uint32_t Knowledge::getInputsNum() {
        return this->inputsNum;
    }

    uint32_t Knowledge::getOutputsNum() {
        return this->outputsNum;
    }

    Experience* Knowledge::getExperience(uint32_t index) {
        return this->experiences[index];
    }

    Experience* Knowledge::getExperiences() {
        return this->experiences;
    }

    uint32_t Knowledge::getExperiencesNum() {
        return this->experiencesNum;
    }
}
