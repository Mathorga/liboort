#include "Convolutional2DLayer.h"

namespace oort {
    void Convolutional2DLayer::step(const math::dtensor input) {
        // Create a temporary 3D input tensor of dimensions inWidth, inHeight, channelsNum.
        math::dtensor3d input3d;
        math::alloc(&input3d, this->inWidth, this->inHeight, this->inChannelsNum);

        // Copy general input tensor to temporary 3D tensor.
        math::copy(input3d, input);

        // Temporary out size.
        uint32_t outWidth = (this->inWidth - this->filterWidth + this->horizontalPadding + this->horizontalStride) / this->horizontalStride;
        uint32_t outHeight = (this->inHeight - this->filterHeight + this->verticalPadding + this->verticalStride) / this->verticalStride;

        
    }
    void Convolutional2DLayer::backprop() {}
    void Convolutional2DLayer::print() {}
}