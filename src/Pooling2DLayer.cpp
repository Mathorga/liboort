#include "Pooling2DLayer.h"

namespace oort {
    Pooling2DLayer::Pooling2DLayer(const uint32_t inWidth, const uint32_t inHeight, const uint32_t channelsNum, const uint32_t poolWidth, const uint32_t poolHeight) :
    PoolingLayer(inWidth * inHeight * channelsNum, (inWidth / poolWidth) * (inHeight / poolHeight) * channelsNum, channelsNum) {
        // Set default stride to pool width in order not to overlap pool samples.
        this->horizontalStride = poolWidth;
        this->verticalStride = poolHeight;

        // Set padding.
        this->horizontalPadding = 0;
        this->verticalPadding = 0;

        // Set accepted input width.
        this->inWidth = inWidth;

        // Set accepted input height.
        this->inHeight = inHeight;

        // Set filter width.
        this->poolWidth = poolWidth;

        // Set filter height.
        this->poolHeight = poolHeight;

        // Allocate composed values.
        math::alloc(&(this->composedValues), inWidth / poolHeight, inHeight / poolHeight);

        // Allocate activated values.
        math::alloc(&(this->activatedValues), inWidth / poolHeight, inHeight / poolHeight);
    }

    void Pooling2DLayer::step(math::dtensor input) {
        // Create a temporary 2D input tensor.
        math::dtensor2d input2d;
        math::alloc(&input2d, this->inWidth, this->inHeight);

        // for () {
        // }
    }

    uint32_t Pooling2DLayer::getHorizontalStride() {
        return this->horizontalStride;
    }
}