/*
********************************************************************************
Brain.h

This file defines a general neural network interface, comprehensive of all the basic
access methods and the standard behavior.
Copyright (C) 2019  Luka Micheletti

********************************************************************************
*/

#ifndef __BRAIN__
#define __BRAIN__

#include "Model.h"
#include "utils.h"

// General neural network interface.
class Brain {
public:
    // Execute one iteration of the net.
    virtual void run() = 0;
    // Bacpropagate the error of the net and correct weights.
    virtual void correct() = 0;
    // Set the input of the net via an array of values.
    virtual void setInput(float* input) = 0;
    // Set the expected output to calculate the error for training.
    virtual void setExpectedOutput(float* expectedOutput) = 0;
    // Return an array containing all the values of the output neurons.
    virtual float *getOutput() = 0;

    // Return the number of input neurons of the net.
    virtual uint16_t getInputNum() = 0;
    // Return the number of output neurons of the net.
    virtual uint16_t getOutputNum() = 0;
    // Return the number of hidden neurons of the net.
    virtual uint16_t getHiddenNum() = 0;
    // Return the total number of neurons of the net.
    virtual uint16_t getNeuronsNum() = 0;
    // Return the total number of synapses of the net.
    virtual uint16_t getSynapsesNum() = 0;

    // Returns the whole model of the network.
    virtual Model* getModel() = 0;
    // Returns all the neurons of the net.
    virtual Model::_Neuron* getNeurons() = 0;
    // Returns all the synapses of the net.
    virtual Model::_Synapse* getSynapses() = 0;

    // Compute the value of a neuron of the net.
    virtual float calculateNeuronValue(uint16_t neuronNum) = 0;
    // Activation function of the neurons of the net.
    virtual float activate(float input) = 0;
    // Derivative of the activation function of the neurons of the net.
    virtual float dActivate(float input) = 0;

    // Mutate the net by adding a synapse.
    virtual bool addSynapse(uint16_t inputNeuron, uint16_t outputNeuron) = 0;
    // Mutate the net by adding a neuron.
    virtual bool addNeuron(uint16_t inputNeuron, uint16_t outputNeuron) = 0;

    // Describe the element through a string.
    virtual void describe() = 0;

protected:

    // Structure of the network.
    Model* model;

    // Learning rate of the net.
    float learningRate;

    float* expectedOutput;

    // Computes all the values of the neurons of the net, in order to calculate the outputs.
    virtual void computeValue() = 0;

    // Compute all the errors of the neurons of the net.
    virtual void computeError() = 0;

    // Adjust the weights of the net's synapses based on the neurons' errors.
    virtual void adjustWeights() = 0;
};

#endif
