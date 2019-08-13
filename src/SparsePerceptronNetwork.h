#ifndef __SPARSE_PERCEPTRON_NETWORK__
#define __SPARSE_PERCEPTRON_NETWORK__

#include "NeuralNetwork.h"
#include "SparsePerceptronModel.h"

namespace Oort {
    class SparsePerceptronNetwork : public NeuralNetwork {
    public:
        // Constructors.
        SparsePerceptronNetwork();
        SparsePerceptronNetwork(vector_size_t inputsNum, vector_size_t outputsNum);
        SparsePerceptronNetwork(SparsePerceptronModel* model);

        void run();
        void correct();
        void train(Knowledge* knowledge, uint32_t iterationsNum);
        neuron_value_t activate(perceptron_input_t value);
        neuron_value_t dActivate(perceptron_input_t value);
        void print();

        // Getters.
        // Returns the whole model of the network.
        SparsePerceptronModel* getModel();
        neuron_value_t* getInput();
        neuron_value_t* getOutput();

        // Setters.
        void setInput(neuron_value_t* input);
        void setInput(Vector<neuron_value_t>* input);
        void setExpectedOutput(neuron_value_t* expectedOutput);

    protected:
        synapse_weight_t baseWeight;
        neuron_value_t baseValue;
        learning_rate_t learningRate;

        void computeValue();
        void computeError();
        void adjustWeights();

        SparsePerceptronModel* model;
    };
}

#endif
