#ifndef __DATASET__
#define __DATASET__

#include "Experience.h"

namespace Oort {
    // Experiences need to be consistent in input and output numbers.
    class Dataset {
    public:
        static const vector_size_t DEFAULT_INPUTS_NUM;
        static const vector_size_t DEFAULT_OUTPUTS_NUM;

        Dataset();
        Dataset(vector_size_t inputsNum, vector_size_t outputsNum);

        void addExperience(Experience* experience);
        void addExperiences(Experience* experiences, vector_size_t size);
        void addExperiences(Vector<Experience>* experiences);
        void print();

        // Getters.
        vector_size_t getInputsNum();
        vector_size_t getOutputsNum();
        Experience* getExperience(vector_size_t index);
        Experience* getExperiences();
        Vector<Experience>* getExperiencesVector();
        vector_size_t getExperiencesNum();

    private:
        vector_size_t inputsNum;
        vector_size_t outputsNum;
        Vector<Experience>* experiences;
    };
}

#endif