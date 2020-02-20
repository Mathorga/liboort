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
        // Sets values to the first layer of neurons.
        void feed(math::dtensor1d inputValues);
        // Sets the activation function for all the layers of the network.
        // The new function is applied to all mem loops as well.
        void setActivation(math::DUnFunc* function);

        // Accessors.
        // Returns neuron values from the output layer.
        math::dtensor1d getOutput();
        uint32_t getOutputSize();
        uint32_t getLayersNum();
        uint32_t getLayerSize(uint32_t index);
        math::itensor1d getLayerDeps(uint32_t index);
        math::dtensor1d getLayerActivatedVals(uint32_t index);

    private:
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
