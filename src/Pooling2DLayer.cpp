#include "Pooling2DLayer.h"

namespace oort {
    Pooling2DLayer::Pooling2DLayer(const uint32_t inWidth,
                                   const uint32_t inHeight,
                                   const uint32_t channelsNum,
                                   const uint32_t poolWidth,
                                   const uint32_t poolHeight) :
    PoolingLayer(inWidth * inHeight * channelsNum,
                 (inWidth / poolWidth) * (inHeight / poolHeight) * channelsNum,
                 channelsNum) {
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
        math::alloc(&(this->composedValues), inWidth / poolWidth, inHeight / poolHeight, channelsNum);

        // Allocate activated values.
        math::alloc(&(this->activatedValues), inWidth / poolWidth, inHeight / poolHeight, channelsNum);
    }

    Pooling2DLayer::Pooling2DLayer(const uint32_t horizontalStride,
                                   const uint32_t verticalStride,
                                   const uint32_t horizontalPadding,
                                   const uint32_t verticalPadding,
                                   const uint32_t inWidth,
                                   const uint32_t inHeight,
                                   const uint32_t channelsNum,
                                   const uint32_t poolWidth,
                                   const uint32_t poolHeight) :
    PoolingLayer(inWidth * inHeight * channelsNum,
                 ((inWidth - poolWidth + horizontalPadding + horizontalStride) / horizontalStride) * ((inHeight - poolHeight + verticalPadding + verticalStride) / verticalStride) * channelsNum,
                 channelsNum) {
        // Set stride.
        this->horizontalStride = horizontalStride;
        this->verticalStride = verticalStride;

        // Set padding.
        this->horizontalPadding = horizontalPadding;
        this->verticalPadding = verticalPadding;

        // Set accepted input width.
        this->inWidth = inWidth;

        // Set accepted input height.
        this->inHeight = inHeight;

        // Set filter width.
        this->poolWidth = poolWidth;

        // Set filter height.
        this->poolHeight = poolHeight;

        // Allocate composed values.
        math::alloc(&(this->composedValues),
                    (inWidth - poolWidth + horizontalPadding + horizontalStride) / horizontalStride,
                    (inHeight - poolHeight + verticalPadding + verticalStride) / verticalStride,
                    channelsNum);

        // Allocate activated values.
        math::alloc(&(this->activatedValues),
                    (inWidth - poolWidth + horizontalPadding + horizontalStride) / horizontalStride,
                    (inHeight - poolHeight + verticalPadding + verticalStride) / verticalStride,
                    channelsNum);
    }

    void Pooling2DLayer::step(math::dtensor input) {
        // Create a temporary 3D input tensor of dimensions inWidth, inHeight, channelsNum.
        math::dtensor3d input3d;
        math::alloc(&input3d, this->inWidth, this->inHeight, this->channelsNum);

        // Copy general input tensor to temporary 3D tensor.
        math::copy(input3d, input);

        // Temporary out size.
        uint32_t outWidth = (this->inWidth - this->poolWidth + this->horizontalPadding + this->horizontalStride) / this->horizontalStride;
        uint32_t outHeight = (this->inHeight - this->poolHeight + this->verticalPadding + this->verticalStride) / this->verticalStride;

        // Loop through channels.
        for (uint32_t channel = 0; channel < input3d.depth; channel++) {
            // Loop through output rows.
            for (uint32_t row = 0; row < outHeight; row ++) {
                // Loop through output cols.
                for (uint32_t col = 0; col < outWidth; col++) {
                    //TODO This whole block can be extracted to a dedicated function.
                    // Loop through values in the current pool.
                    for (uint32_t i = 0; i < this->poolWidth; i++) {
                        for (uint32_t j = 0; j < this->poolHeight; j++) {
                            
                        }
                    }
                }
            }
        }
    }

    uint32_t Pooling2DLayer::getHorizontalStride() {
        return this->horizontalStride;
    }
}