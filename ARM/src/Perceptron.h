#ifndef __PERCEPTRON__
#define __PERCEPTRON__

#include "Neuron.h"
#include "PerceptronSynapse.h"
#include "Vector.h"

#define perceptron_error_t uint16_t
#define perceptron_input_t uint32_t
#define synapses_num_t uint16_t

// class Vector<PerceptronSynapse>;

class PerceptronSynapse;

class Perceptron : public Neuron {
public:
    // Constructors.
    Perceptron();
    Perceptron(Neuron& neuron);

    void print();

    // Getters.
    float getFloatValue();
    perceptron_error_t getError();
    neuron_value_t getExpectedOutput();
    synapses_num_t getSynapsesNum();
    Vector<PerceptronSynapse>* getSynapses();
    Perceptron** getInputs();

    // Setters.
    void setDValue(neuron_value_t dValue);
    void setError(perceptron_error_t error);
    void addError(perceptron_error_t error);
    void setExpectedOutput(neuron_value_t expectedOutput);

private:
    neuron_value_t dValue;
    perceptron_error_t error;
    neuron_value_t expectedOutput;
    perceptron_error_t delta;
    perceptron_error_t partialDelta;

    // synapses_num_t synapsesNum;
    Vector<PerceptronSynapse>* synapses;
    // PerceptronSynapse** synapses;
};

#endif
