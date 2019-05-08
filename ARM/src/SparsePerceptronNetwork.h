#ifndef __SPARSE_PERCEPTRON_NETWORK__
#define __SPARSE_PERCEPTRON_NETWORK__

#include "NeuralNetwork.h"
#include "SparsePerceptronModel.h"

#define learning_rate_t float

class SparsePerceptronNetwork : public NeuralNetwork {
public:
    // Constructors.
    SparsePerceptronNetwork();
    SparsePerceptronNetwork(neurons_num_t inputsNum, neurons_num_t outputsNum);
    SparsePerceptronNetwork(SparsePerceptronModel* model);

    void run();
    void correct();
    neuron_value_t activate(perceptron_input_t value);
    neuron_value_t dActivate(perceptron_input_t value);
    void print();

    // Getters.
    // Returns the whole model of the network.
    SparsePerceptronModel* getModel();
    neuron_value_t* getOutput();

    // Setters.
    void setExpectedOutput(neuron_value_t* expectedOutput);

protected:
    synapse_weight_t baseWeight;
    neuron_value_t baseValue;
    learning_rate_t learningRate;
    // neuron_value_t* expectedOutput;

    void computeValue();
    void computeError();
    void adjustWeights();

    SparsePerceptronModel* model;
};

#endif
