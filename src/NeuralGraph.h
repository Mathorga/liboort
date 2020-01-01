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

#include "utils.h"

#define array_size_t uint32_t
#define neuron_value_t double
#define synapse_weight_t double
#define layer_id_t uint8_t

namespace Oort {

    class NeuralGraph {
    public:
        static const array_size_t DEFAULT_LAYERS_NUM;
        static const array_size_t DEFAULT_LAYER_SIZE;

        enum Activation {
            active = 1,
            inactive = 0
        };

        struct Layer {
            // Structure containing every neuron value in a single layer.
            neuron_value_t* neuronValues;
            array_size_t neuronsNum;

            // The structure defines the direction of connections between
            // layers: each element is an array that represents all the layers
            // the current one has connections to.
            layer_id_t* targets;
            array_size_t targetsNum;

            // Structure containing synapse weights coming from the layer.
            // Every element is an array of 2D matrices of values representing
            // connections between the current layer and another one referred by
            // <targets> at the same index.
            synapse_weight_t** synapseWeights;

            // Since some synapses may be inactive, an activation is used to
            // enable or disable them during computations.
            // The structure has the same size as <synapseWeights> and its
            // values can only be 1 or 0.
            // Every element is an array of 2D matrices whose values are
            // multiplicated to the corrisponding weight matrix using the
            // Hadamard product.
            Activation** synapseActivations;
        };

        // Constructors.
        NeuralGraph();
        // Creates a standard feedforward neural network, since no custom
        // structure is defined.
        NeuralGraph(array_size_t layersNum, array_size_t* layerSizes);

        // Getters.
        neuron_value_t** getNeuronValues();
        synapse_weight_t** getSynapseWeights();
        Activation** getSynapseActivations();

    private:
        struct Layer* layers;
        array_size_t layersNum;
    };
}

#endif
