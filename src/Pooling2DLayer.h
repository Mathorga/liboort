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

        // Layer values before activation.
        math::dtensor2d composedValues;

        // Layer values after activation.
        math::dtensor2d activatedValues;

    public:
        // Full constructor: creates a 2D pooling layer from all given sizes.
        // @param inWidth The width the input tensor has to be.
        // @param inHeight The height the input tensor has to be.
        // @param channelsNum The number of channel the layer works on (number of accepted channels).
        // @param poolWidth The width of the pool to apply to the input tensor.
        // @param poolHeight The height of the pool to apply to the input tensor.
        Pooling2DLayer(const uint32_t inWidth, const uint32_t inHeight, const uint32_t channelsNum, const uint32_t poolWidth, const uint32_t poolHeight);

        void step(math::dtensor input);

        // Returns the horizontal stride.
        // @return The horizontal stride.
        uint32_t getHorizontalStride();

    };
}

#endif