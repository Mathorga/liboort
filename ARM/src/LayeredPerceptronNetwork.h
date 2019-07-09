#ifndef __LAYERED_PERCEPTRON_NETWORK__
#define __LAYERED_PERCEPTRON_NETWORK__

#include "NeuralNetwork.h"

class LayeredPerceptronNetwork : public NeuralNetwork {
public:
    // Constructors.
    LayeredPerceptronNetwork();

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

private:
    synapse_weight_t baseWeight;
    neuron_value_t baseValue;
    learning_rate_t learningRate;

    void computeValue();
    void computeError();
    void adjustWeights();

    LayeredPerceptronModel* model;
};


#endif
