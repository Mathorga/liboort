/*
********************************************************************************
Convolutional2DLayer.h

TODO

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __CONVOLUTIONAL_2D_LAYER__
#define __CONVOLUTIONAL_2D_LAYER__

#include "ConvolutionalLayer.h"

namespace oort {
    class Convolutional2DLayer : public ConvolutionalLayer {
    private:
        // Horizontal stride for the filtering operation: determines the number of units the filter moves at each horizontal shift.
        uint32_t horizontalStride;

        // Vertical stride for the filtering operation: determines the number of units the filter moves at each vertical shift.
        uint32_t verticalStride;

        // Horizontal padding for the filtering operation: determines the number of units to consider to the left and right of the input data.
        uint32_t horizontalPadding;

        // Vertical padding for the filtering operation: determines the number of units to consider above and below the input data.
        uint32_t verticalPadding;

        // Expected width of the input tensor.
        uint32_t inWidth;

        // Expected height of the input tensor.
        uint32_t inHeight;

        // Filters to convolute the input with.
        // The number of filters determines the number of output channels (or at least has to be the same).
        math::dtensor3d* filters;

        // Width of the applied filter.
        uint32_t filterWidth;

        // Height of the applied filter.
        uint32_t filterHeight;

        // Layer values before activation.
        math::dtensor3d composedValues;

        // Layer values after activation.
        math::dtensor3d activatedValues;

        // Layer activation function.
        math::DUnFunc* activationFunction;

        // Apply the channel-th filter to the given input.
        // @param input The input tensor to convolute on.
        // @param channel The specific output channel to convolute on.
        // @param startColumn The column from which to start convoluting (the size of the filter is specified by the associated member).
        // @param startRow The row from which to start convoluting (the size of the filter is specified by the associated member).
        // @return The computed output of the convolution.
        double convolute(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow);

    public:
        void step(const math::dtensor input);
        void backprop();
        void print();
    };
}

#endif
