/*
********************************************************************************
Model.h

Definition of the general structure and behavior of the generic neural graph.
The class can be tuned to represent most of the widely used neural network
types, such as feedforward, sparse, Kohonen maps.
To be tested on spiking neural networks.

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __MODEL__
#define __MODEL__

#include "utils.h"

namespace oort {
    class Model {
    public:
        static const uint32_t DEFAULT_LAYERS_NUM;
        static const uint32_t DEFAULT_LAYER_SIZE;
        static const uint32_t DEFAULT_MEM_LOOPS_NUM;

        enum activation {
            SIGMOID,
            RELU,
            TANH,
            SOFTMAX,
            LINEAR
        };

        // Maybe a dedicated class should be created.
        // For now, since the layer should perform no actions, it should be good
        // as it is.
        struct Layer {
            // Structure containing every unactivated value in a single layer.
            math::dtensor1d composedValues;
            // Structure containing every activated value in a single layer.
            math::dtensor1d activatedValues;

            // The structure defines the direction of connections between
            // layers: each element is the index of a layer the current one has
            // connections from.
            math::itensor1d dependencies;

            // Structure containing weights coming to the layer.
            // Each element is an array of 2D tensors of values representing
            // connections between the current layer and another one referred by
            // <dependencies> at the same index.
            math::dtensor2d* weights;

            // Structure containing biases coming to the layer.
            // Each element is a 1D tensor of values used to provide fixed
            // values to the layer.
            math::dtensor1d* biases;

            // Since some synapses may be inactive, an activation is used to
            // enable or disable them during computations.
            // The structure has the same size as <weights> and its
            // values can only be 1 or 0.
            // Every element is an array of 2D matrices whose values are
            // multiplicated to the corrisponding weight matrix using the
            // Hadamard product.
            math::dtensor2d* weightActivations;

            // Do I also need a bias activation???

            // Add an activation function to the layer itself, in order to
            // differentiate between each layer.
            math::DUnFunc* activationFunction;
        };

        // Constructors.
        // Creates a recurrent neural network using the specified mem loops and
        // the specified layer sizes.
        Model(uint32_t memLoopsNum, uint32_t layersNum, uint32_t* layerSizes);
        // Creates a standard feedforward neural network, since no custom
        // structure is defined.
        Model(uint32_t layersNum, uint32_t* layerSizes);
        // Creates a standard feedforward neural network with fixed layer size,
        // since no custom structure is defined.
        Model(uint32_t layersNum);
        Model();

        // Computes the value of the whole neural network.
        void compute();

        // Getters.
        // Returns neuron values from the output layer.
        double* getOutput();
        uint32_t getOutputSize();

        // Setters.
        // Sets values to the first layer of neurons.
        void feed(math::dtensor1d inputValues);

    private:
        // The 2D Tensor represents the structure of the network.
        // In order to include the case of recurrent neural network, more than
        // one neural network need to be hold in memory.
        // To do so, a 2D tensor is used. Its width represents the number of
        // layers of the network, while its height represents the number of
        // memory loops of the network.
        // math::tensor2d<Layer> layers;

        // Number of memory loops, used to implement recurrent neural networks.
        uint32_t memLoopsNum;
        // Number of layers in each memory loop.
        uint32_t layersNum;
        // Actual layers of the network.
        Layer** layers;

        void shift();
    };
}

#endif
