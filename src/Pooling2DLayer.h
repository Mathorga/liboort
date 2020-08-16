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

        // Performs a max pooling operation given an input tensor and starting positions.
        // @param input The input tensor to pool over.
        // @param channel The specific channel to pool over.
        // @param startColumn The column from which to start pooling (the size of the pool is specified by the associated member).
        // @param startRow The row from which to start pooling (the size of the pool is specified by the associated member).
        double maxPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow);

        // Performs an average pooling operation given an input tensor and starting positions.
        // @param input The input tensor to pool over.
        // @param channel The specific channel to pool over.
        // @param startColumn The column from which to start pooling (the size of the pool is specified by the associated member).
        // @param startRow The row from which to start pooling (the size of the pool is specified by the associated member).
        double avgPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow);

        // Performs a min pooling operation given an input tensor and starting positions.
        // @param input The input tensor to pool over.
        // @param channel The specific channel to pool over.
        // @param startColumn The column from which to start pooling (the size of the pool is specified by the associated member).
        // @param startRow The row from which to start pooling (the size of the pool is specified by the associated member).
        double minPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow);

        // Performs a median pooling operation given an input tensor and starting positions.
        // @param input The input tensor to pool over.
        // @param channel The specific channel to pool over.
        // @param startColumn The column from which to start pooling (the size of the pool is specified by the associated member).
        // @param startRow The row from which to start pooling (the size of the pool is specified by the associated member).
        double medPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow);

        // Returns the horizontal stride.
        // @return The horizontal stride.
        uint32_t getHorizontalStride();

        // Returns the vertical stride.
        // @return The vertical stride.
        uint32_t getVerticalStride();

        // Returns the horizontal padding.
        // @return The horizontal padding.
        uint32_t getHorizontalPadding();

        // Returns the vertical padding.
        // @return The vertical padding.
        uint32_t getVerticalPadding();

        // Returns the input width.
        // @return The input width.
        uint32_t getInWidth();

        // Returns the input height.
        // @return The input height.
        uint32_t getInHeight();

        // Returns the pool width.
        // @return The pool width.
        uint32_t getPoolWidth();

        // Returns the pool height.
        // @return The pool height.
        uint32_t getPoolHeight();

        // Returns the set pooling function.
        // @return The set pooling function.
        PoolingFunction getPoolingFunction();

        // Returns the composed values tensor.
        // @return The composed values tensor.
        math::dtensor3d getComposedValues();

        // Returns the activated values tensor.
        // @return The activated values tensor.
        math::dtensor3d getActivatedValues();

        // Returns the layer activation function.
        // @return The layer activation function.
        math::DUnFunc* getActivationFunction();

        // Sets the horizontal stride.
        // @param horizontalStride The horizontal stride to set.
        void setHorizontalStride(const uint32_t horizontalStride);

        // Sets the vertical stride.
        // @param verticalStride The vertical stride to set.
        void setVerticalStride(const uint32_t verticalStride);

        // Sets the horizontal padding.
        // @param horizontalPadding The horizontal padding to set.
        void setHorizontalPadding(const uint32_t horizontalPadding);

        // Sets the vertical padding.
        // @param verticalPadding The vertical padding to set.
        void setVerticalPadding(const uint32_t verticalPadding);

        // Sets the pool width.
        // @param poolWidth The pool width to set.
        void setPoolWidth(const uint32_t poolWidth);

        // Sets the pool height.
        // @param poolHeight The pool height to set.
        void setPoolHeight(const uint32_t poolHeight);

        // Sets the pooling function (MAX, AVG, MIN, MED).
        // @param poolingFunction The pooling function to set (MAX, AVG, MIN, MED).
        void setPoolingFunction(const PoolingFunction poolingFunction);

        // Sets the layer activation function.
        // @param activationFunction The activation function to set.
        void setActivationFunction(math::DUnFunc* activationFunction);

    };
}

#endif