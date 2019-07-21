#ifndef __KNOWLEDGE__
#define __KNOWLEDGE__

#include "Experience.h"

// Experiences need to be consistent in input and output numbers.
class Knowledge {
public:
    static const vector_size_t DEFAULT_INPUTS_NUM;
    static const vector_size_t DEFAULT_OUTPUTS_NUM;

    Knowledge();
    Knowledge(vector_size_t inputsNum, vector_size_t outputsNum);

    void addExperience(Experience* newExperience);
    void addExperiences(Experience* newExperiences, vector_size_t size);
    void addExperiences(Vector<Experience>* newExperiences);
    void print();

    // Getters.
    vector_size_t getInputsNum();
    vector_size_t getOutputsNum();
    Experience* getExperiences();
    Vector<Experience>* getExperiencesVector();

private:
    vector_size_t inputsNum;
    vector_size_t outputsNum;
    Vector<Experience>* experiences;
};

#endif
