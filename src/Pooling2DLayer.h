/*
********************************************************************************
Pooling2DLayer.h

The class implements a standard pooling layer on multi-channel 2D input.

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __POOLING_2D_LAYER__
#define __POOLING_2D_LAYER__

#include "PoolingLayer.h"
#include "utils.h"

namespace oort {
    class Pooling2DLayer : public PoolingLayer {
    private:
        // Horizontal stride for the pooling operation: determines the number of units the pool moves at each horizontal shift.
        uint32_t horizontalStride;

        // Vertical stride for the pooling operation: determines the number of units the pool moves at each vertical shift.
        uint32_t verticalStride;

        // Horizontal padding for the pooling operation: determines the number of units to consider to the left and right of the input data.
        uint32_t horizontalPadding;

        // Vertical padding for the pooling operation: determines the number of units to consider above and below the input data.
        uint32_t verticalPadding;

        // Expected width of the input tensor.
        uint32_t inWidth;

        // Expected height of the input tensor.
        uint32_t inHeight;

        // Width of the applied pool.
        uint32_t poolWidth;

        // Height of the applied pool.
        uint32_t poolHeight;

        // Function to be applied to each pool.
        PoolingFunction poolingFunction;

        // Layer values before activation.
        math::dtensor3d composedValues;

        // Layer values after activation.
        math::dtensor3d activatedValues;

        // Layer activation function.
        math::DUnFunc* activationFunction;

    public:
        // Unstrided unpadded constructor: creates a 2D pooling layer with stride equal to the pool size and zero padding.
        // @param inWidth The width the input tensor has to be.
        // @param inHeight The height the input tensor has to be.
        // @param channelsNum The number of channel the layer works on (number of accepted channels).
        // @param poolWidth The width of the pool to apply to the input tensor.
        // @param poolHeight The height of the pool to apply to the input tensor.
        Pooling2DLayer(const uint32_t inWidth,
                       const uint32_t inHeight,
                       const uint32_t channelsNum,
                       const uint32_t poolWidth,
                       const uint32_t poolHeight);

        // Full constructor: creates a 2D pooling layer given stride and padding.
        // @param horizontalStride The amount of positions to move between horizontal samplings.
        // @param verticalStride The amount of positions to move between vertical samplings.
        // @param horizontalPadding The number of units to consider above and below the input data.
        // @param verticalPadding The number of units to consider to the left and right of the input data.
        // @param inWidth The width the input tensor has to be.
        // @param inHeight The height the input tensor has to be.
        // @param channelsNum The number of channel the layer works on (number of accepted channels).
        // @param poolWidth The width of the pool to apply to the input tensor.
        // @param poolHeight The height of the pool to apply to the input tensor.
        // @param poolingFunction The pooling function to be used (MAX, AVG, MIN, MED).
        // @param activationFunction The activation function to be applied to the layer.
        Pooling2DLayer(const uint32_t horizontalStride,
                       const uint32_t verticalStride,
                       const uint32_t horizontalPadding,
                       const uint32_t verticalPadding,
                       const uint32_t inWidth,
                       const uint32_t inHeight,
                       const uint32_t channelsNum,
                       const uint32_t poolWidth,
                       const uint32_t poolHeight,
                       const PoolingFunction poolingFunction,
                       math::DUnFunc* activationFunction);

        void step(const math::dtensor input);
        void backprop();
        void print();

        //TODO Extract to utility file.
        double maxPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow);
        double avgPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow);
        double minPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow);
        double medPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow);

        // Returns the horizontal stride.
        // @return The horizontal stride.
        uint32_t getHorizontalStride();

    };
}

#endif