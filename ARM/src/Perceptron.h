#ifndef __PERCEPTRON__
#define __PERCEPTRON__

#include "Neuron.h"
#include "PerceptronSynapse.h"
#include "Vector.h"

#define perceptron_error_t float
#define perceptron_input_t float

class PerceptronSynapse;

class Perceptron : public Neuron {
public:
    static const neuron_value_t DEFAULT_VALUE;
    static Perceptron getNullPerceptron();

    // Constructors.
    Perceptron(neurons_num_t id);
    Perceptron(neurons_num_t id, neuron_value_t value);
    Perceptron(neurons_num_t id, neuron_value_t value, Neuron::NeuronType type);
    Perceptron(neurons_num_t id, neuron_value_t value, vector_size_t synapsesNum);
    Perceptron(Neuron& neuron);

    void print();

    // Getters.
    neuron_value_t getDValue();
    perceptron_error_t getError();
    neuron_value_t getExpectedOutput();
    vector_size_t getSynapsesNum();
    Vector<PerceptronSynapse>* getSynapses();
    PerceptronSynapse* getSynapse(vector_size_t index);
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

    Vector<PerceptronSynapse>* synapses;
};

#endif
