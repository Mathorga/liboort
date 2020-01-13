/*
*********************************************************************************
LayeredPerceptronNetwork.h

This file defines the interface for a standard perceptron deep neural network.

Copyright (C) 2019 Luka Micheletti
*********************************************************************************
*/

#ifndef __LAYERED_PERCEPTRON_NETWORK__
#define __LAYERED_PERCEPTRON_NETWORK__

#include "NeuralNetwork.h"
#include "LayeredPerceptronModel.h"

namespace Oort {
    class LayeredPerceptronNetwork : public NeuralNetwork {
    public:
        static const perceptron_error_t UNSET_ERROR;
        static const learning_rate_t DEFAULT_LEARNING_RATE;
        // static const momentum_t DEFAULT_MOMENTUM;

        // Constructors.
        LayeredPerceptronNetwork();
        LayeredPerceptronNetwork(LayeredPerceptronModel* model);

        void run();
        // void correct();
        // Trains the network through so-called "batch training", so all the
        // weights are upgraded only after batchSize experiences have been
        // processed.
        // If batchSize == knowledge size, then the training results in complete
        // batch training; if batchSize == 1, then the training results in
        // on-line training.
        void train(Knowledge* knowledge, uint32_t epochsNum, uint32_t batchSize);
        neuron_value_t activate(neuron_value_t value);
        neuron_value_t dActivate(neuron_value_t value);
        void print();

        // Getters.
        // Returns the whole model of the network.
        LayeredPerceptronModel* getModel();
        neuron_value_t* getOutput();
        perceptron_error_t getError();

        // Setters.
        void setModel(LayeredPerceptronModel* model);
        void setInput(neuron_value_t* input);
        void setInput(Vector<neuron_value_t>* input);

        // Sets the expected output for all output neurons.
        // Be careful using this method, because no array length information is used:
        // <void setExpectedOutput(Vector<Vector<neuron_value_t>>* expectedOutput)> is to be preferred if the array
        // length can be inaccurate.
        // Expected output array size must be at least as big as model's total output neurons number in order for it to
        // work properly.
        void setExpectedOutput(neuron_value_t* expectedOutput);
        // Set the expected output for all output neurons.
        // Expected output vector size must be at least as big as model's output layer size.
        bool setExpectedOutput(Vector<neuron_value_t>* expectedOutput);
        void setLearningRate(learning_rate_t learningRate);
        void computeError();
        void adjustWeights(uint32_t batchSize);
    private:
        synapse_weight_t baseWeight;
        neuron_value_t baseValue;
        learning_rate_t learningRate;
        // momentum_t momentum;
        // Vector<perceptron_error_t>* errors;
        perceptron_error_t error;
        vector_size_t batchSize;

        void computeValue();
        // void computeError();
        // void adjustWeights();

        LayeredPerceptronModel* model;
    };
}

#endif