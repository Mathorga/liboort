#ifndef __PERCEPTRON__
#define __PERCEPTRON__

#include "Neuron.h"
#include "PerceptronSynapse.h"

#define neuron_error_t uint16_t
#define synapses_num_t uint16_t

class PerceptronSynapse;

class Perceptron : public Neuron {
public:
    // Constructors.
    Perceptron();
    Perceptron(Neuron& neuron);

    // Getters.
    float getFloatValue();
    neuron_error_t getError();
    neuron_value_t getExpectedOutput();
    synapses_num_t getSynapsesNum();
    PerceptronSynapse** getSynapses();
    Perceptron** getInputs();

    // Setters.
    void setDValue(neuron_value_t dValue);
    void setError(neuron_error_t error);
    void addError(neuron_error_t error);
    void setExpectedOutput(neuron_value_t expectedOutput);

private:
    neuron_value_t dValue;
    neuron_error_t error;
    neuron_value_t expectedOutput;
    neuron_error_t delta;
    neuron_error_t partialDelta;

    synapses_num_t synapsesNum;
    PerceptronSynapse** synapses;
};

#endif
