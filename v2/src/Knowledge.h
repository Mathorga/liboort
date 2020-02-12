#ifndef __KNOWLEDGE__
#define __KNOWLEDGE__

#include "Experience.h"

namespace oort {
    // Experiences need to be consistent in input and output numbers.
    class Knowledge {
    public:
        static const uint32_t DEFAULT_INPUTS_NUM;
        static const uint32_t DEFAULT_OUTPUTS_NUM;

        Knowledge(uint32_t inputsNum, uint32_t outputsNum);
        Knowledge();

        void addExperience(Experience* experience);
        void addExperiences(Experience* experiences, uint32_t size);
        void print();

        // Getters.
        uint32_t getInputsNum();
        uint32_t getOutputsNum();
        Experience* getExperience(uint32_t index);
        Experience* getExperiences();
        uint32_t getExperiencesNum();

    private:
        uint32_t inputsNum;
        uint32_t outputsNum;
        uint32_t experiencesNum;
        Experience* experiences;
    };
}

#endif
