#ifndef __LAYERED_PERCEPTRON_NETWORK__
#define __LAYERED_PERCEPTRON_NETWORK__

#include "NeuralNetwork.h"
#include "LayeredPerceptronModel.h"

namespace Oort {
    class LayeredPerceptronNetwork : public NeuralNetwork {
    public:
        // Constructors.
        LayeredPerceptronNetwork();
        LayeredPerceptronNetwork(LayeredPerceptronModel* model);

        void run();
        void correct();
        void train(Knowledge* knowledge, uint32_t iterationsNum);
        neuron_value_t activate(perceptron_input_t value);
        neuron_value_t dActivate(perceptron_input_t value);
        void print();

        // Getters.
        // Returns the whole model of the network.
        LayeredPerceptronModel* getModel();
        neuron_value_t* getOutput();

        // Setters.
        void setModel(LayeredPerceptronModel* model);
        void setInput(neuron_value_t* input);
        void setInput(Vector<neuron_value_t>* input);
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
}


#endif
