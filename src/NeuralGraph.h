/*
********************************************************************************
NeuralGraph.h

Definition of the general structure and behavior of the generic neural graph.
The class can be tuned to represent most of the widely used neural network
types, such as feedforward, sparse, Kohonen maps.
To be tested on spiking neural networks.

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __NEURAL_GRAPH__
#define __NEURAL_GRAPH__

#define neuron_value_t double
#define synapse_weight_t double
#define layers_num_t uint8_t
#define layer_size_t uint32_t
#define layer_id_t uint8_t

namespace Oort {

    class NeuralGraph {
    public:
        static const layers_num_t DEFAULT_LAYERS_NUM;
        static const layer_size_t DEFAULT_LAYER_SIZE;

        enum Activation {
            active = 1,
            inactive = 0
        }

        // Constructors.
        NeuralGraph();

        // Getters.
        neuron_value_t** getNeuronValues();
        synapse_weight_t** getSynapseWeights();
        ActivationType** getSynapseActivations();

    private:
        // The following structures define the shape of the whole neural graph.
        // Structure containing every neuron's value.
        // Every element is an array of values representing a classic Neural
        // Network layer of neurons.
        neuron_value_t** neuronValues;
        // Structure containing every synapse's weight.
        // Every element is a 2D matrix of values representing connections
        // between two layers.
        synapse_weight_t** synapseWeights;
        // Since some synapses may be inactive, an activation is used to enable
        // or disable them during computations.
        // The structure has the same size as <synapseWeights> and its values
        // can only be 1 or 0. Every element is a 2D matrix and its values are
        // multiplicated to the corrisponding weight matrix using the Hadamard
        // product.
        ActivationType** synapseActivations;

        layers_num_t layersNum;
        layer_size_t* layerSizes;

        // The structure defines the direction of connections between layers:
        // each element is an array that represents all the layers the current
        // one has connections to.
        layer_id_t** structure;
    };
}

#endif
