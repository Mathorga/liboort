#ifndef __KNOWLEDGE__
#define __KNOWLEDGE__

#include "Experience.h"

namespace Oort {
    // Experiences need to be consistent in input and output numbers.
    class Knowledge {
    public:
        static const vector_size_t DEFAULT_INPUTS_NUM;
        static const vector_size_t DEFAULT_OUTPUTS_NUM;

        Knowledge();
        Knowledge(uint32_t inputsNum, uint32_t outputsNum);

        void addExperience(Experience* experience);
        void addExperiences(Experience* experiences, uint32_t size);
        void addExperiences(Vector<Experience>* experiences);
        void print();

        // Getters.
        uint32_t getInputsNum();
        uint32_t getOutputsNum();
        Experience* getExperience(uint32_t index);
        math::tensor1d<Experience> getExperiences();
        uint32_t getExperiencesNum();

    private:
        uint32_t inputsNum;
        uint32_t outputsNum;
        math::tensor1d<Experience> experiences;
    };
}

#endif
