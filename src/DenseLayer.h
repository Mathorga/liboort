/*
********************************************************************************
DenseLayer.h

The class implements a fully connected layer defined as:
output = activation((input * weight) + bias)

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __DENSE_LAYER__
#define __DENSE_LAYER__

#include "Layer.h"
#include "utils.h"

namespace oort {
    class DenseLayer : public Layer {
    private:
        // Layer weight matrix.
        math::dtensor2d weight;

        // Layer bias array.
        math::dtensor1d bias;

        // Layer values before activation.
        math::dtensor1d composedValues;

        // Layer values after activation.
        math::dtensor1d activatedValues;

        // Layer activation function.
        math::DUnFunc* activationFunction;

    public:
        // Creates a DenseLayer given its input size and output size.
        // @param inSize The total input size of the layer.
        // @param outSize The total output size of the layer.
        DenseLayer(const uint32_t inSize, const uint32_t outSize);
        void step(math::dtensor input);
        void backprop();
        void print();

        // Getters.
        math::dtensor2d getWeight();
        math::DUnFunc* getActivationFunction();

        // Setters.
        void setActivationFunction(math::DUnFunc* function);
    };
}

#endif
