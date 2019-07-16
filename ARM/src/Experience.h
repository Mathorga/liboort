#ifndef __EXPERIENCE__
#define __EXPERIENCE__

#include "utils.h"
#include "Vector.h"
#include "Neuron.h"

class Experience {
public:
    Experience();
    Experience(vector_size_t inputsNum, vector_size_t outputsNum);
    Experience(vector_size_t inputsNum, neuron_value_t* inputValues, vector_size_t outputsNum, neuron_value_t* outputValues);
    Experience(Vector<neuron_value_t>* inputs, Vector<neuron_value_t>* outputs);

    void print();

    // Getters.
    neuron_value_t* getInputs();
    neuron_value_t* getOutputs();
    Vector<neuron_value_t>* getInputsVector();
    Vector<neuron_value_t>* getOutputsVector();
    vector_size_t getInputsNum();
    vector_size_t getOutputsNum();

    // Setters.
    void setInputs(neuron_value_t* inputs, vector_size_t inputsNum);
    void setOutputs(neuron_value_t* outputs, vector_size_t outputsNum);

private:
    Vector<neuron_value_t>* inputs;
    Vector<neuron_value_t>* outputs;
};

#endif
