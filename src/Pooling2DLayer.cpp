#include "Pooling2DLayer.h"

namespace oort {
    Pooling2DLayer::Pooling2DLayer(const uint32_t inWidth, const uint32_t inHeight, const uint32_t channelsNum, const uint32_t poolWidth, const uint32_t poolHeight) :
    PoolingLayer(inWidth * inHeight * channelsNum, (inWidth / poolWidth) * (inHeight / poolHeight) * channelsNum, channelsNum) {
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
        
    }
}