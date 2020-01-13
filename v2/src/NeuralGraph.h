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

#include "matrix.h"

#define array_size_t uint32_t
#define neuron_value_t double
#define synapse_weight_t double
#define layers_num_t uint8_t
#define loops_num_t uint32_t
#define activation_type_t double

namespace oort {
    class NeuralGraph {
    public:
        static const array_size_t DEFAULT_LAYERS_NUM;
        static const array_size_t DEFAULT_LAYER_SIZE;
        static const array_size_t DEFAULT_LOOPS_NUM;

        // Maybe a dedicated class should be created.
        // For now, since the layer should perform no actions, it should be good
        // as it is.
        struct Layer {
            // Structure containing every neuron value in a single layer.
            neuron_value_t* neuronValues;
            array_size_t neuronsNum;

            // The structure defines the direction of connections between
            // layers: each element is the index of a layer the current one has
            // connections to.
            layers_num_t* targets;
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
            activation_type_t** synapseActivations;
        };

        // Constructors.
        // Creates a standard feedforward neural network, since no custom
        // structure is defined.
        NeuralGraph(layers_num_t layersNum, array_size_t* layerSizes);
        // Creates a standard feedforward neural network with fixed layer size,
        // since no custom structure is defined.
        NeuralGraph(layers_num_t layersNum);
        NeuralGraph();

        // Computes the value of the whole neural network using the specified
        // loops number, meaning that, if there are any backward connections,
        // they are performed <loopsNum> times.
        void computeValue(loops_num_t loopsNum);
        // Computes the value of the whole neural network using the default
        // loops number.
        void computeValue();

        // Getters.
        // Returns neuron values from the output layer.
        neuron_value_t* getOutput();
        array_size_t getOutputSize();

        // Setters.
        // Sets values to the first layer of neurons.
        void setInput(neuron_value_t* inputValues);
        void setInput(neuron_value_t* inputValues, array_size_t inputSize);

    private:
        struct Layer* layers;
        array_size_t layersNum;
    };
}

#endif