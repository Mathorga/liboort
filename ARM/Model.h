/*
********************************************************************************
Model.h

This file defines the base representation of a sparse neural network model.
The model is closer than a standard layered model to the biological brain structure.
The Neuron and Synapse types and the default access methods are defined to manage
the model itself.
Copyright (C) 2019  Luka Micheletti

********************************************************************************
*/

#ifndef __MODEL__
#define __MODEL__

#include "utils.h"

class Model {
public:
    // Definition of the neuron types.
    enum NeuronType {
        typeInput = 0,
        typeOutput = 1,
        typeHidden = 2
    };

    // Definition of the neuron data type.
    typedef struct {
        NeuronType type;
        double value;
        double dValue;
        double error;
        double delta;
        double partialDelta;
        bool enabled;
    } _Neuron;

    // Definition of the synapse data type.
    typedef struct {
        uint16_t inputNeuron;
        uint16_t outputNeuron;
        double weight;
        bool enabled;
    } _Synapse;

    void describe();

    uint16_t getInputNum();
    uint16_t getOutputNum();
    uint16_t getHiddenNum();
    uint16_t getNeuronsNum();
    uint16_t getSynapsesNum();
    _Neuron *getNeurons();
    _Synapse *getSynapses();

    void setInputNum(uint16_t num);
    void setOutputNum(uint16_t num);
    void setHiddenNum(uint16_t num);
    void setNeuronsNum(uint16_t num);
    void setSynapsesNum(uint16_t num);
    void setNeurons(_Neuron *inputNeurons);
    void setSynapses(_Synapse *inputSynapses);

private:
    // Number of input neurons.
    uint16_t inputNum;
    // Number of output neurons.
    uint16_t outputNum;
    // Number of hidden neurons.
    uint16_t hiddenNum;
    // Total number of neurons.
    uint16_t neuronsNum;
    // Total number of synapses.
    uint16_t synapsesNum;

    // Neural network structure: since a neural network is essentially a graph
    // in which nodes are neurons and edges are synapses and the most frequent
    // operation is insertion, the data structure used to represent it is that
    // of two arrays, one for neurons and one for synapses. The need for information
    // on edges lead to discard the adjacency-list and the adjacency matrix
    // representation of graphs.
    _Neuron *neurons;
    _Synapse *synapses;
};

#endif
