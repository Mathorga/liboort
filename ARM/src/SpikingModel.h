#ifndef __SPIKING_MODEL__
#define __SPIKING_MODEL__

#include "utils.h"

class SpikingModel {
public:
    // Definition of the neuron data type.
    typedef struct {
        NeuronType type;
        uint16_t value;
        bool enabled;
        bool state;
        bool outState;
        std::vector<uint32_t> inputs;
    } _Neuron;

    // Definition of the synapse data type.
    // typedef struct {
    //     uint16_t inputNeuron;
    //     uint16_t outputNeuron;
    //     bool state;
    //     bool nextState;
    //     bool enabled;
    // } _Synapse;

    void describe();

    uint16_t getInputNum();
    uint16_t getOutputNum();
    uint16_t getHiddenNum();
    uint16_t getNeuronsNum();
    _Neuron* getNeurons();

    void setInputNum(uint16_t num);
    void setOutputNum(uint16_t num);
    void setHiddenNum(uint16_t num);
    void setNeuronsNum(uint16_t num);
    void setNeurons(_Neuron *inputNeurons);

private:
    // Number of input neurons.
    uint16_t inputNum;
    // Number of output neurons.
    uint16_t outputNum;
    // Number of hidden neurons.
    uint16_t hiddenNum;
    // Total number of neurons.
    uint16_t neuronsNum;

    // Neural network structure: since a neural network is essentially a graph
    // in which nodes are neurons and edges are synapses and the most frequent
    // operation is insertion, the data structure used to represent it is that
    // of two arrays, one for neurons and one for synapses. The need for information
    // on edges lead to discard the adjacency-list and the adjacency matrix
    // representation of graphs.
    _Neuron* neurons;
};

#endif
