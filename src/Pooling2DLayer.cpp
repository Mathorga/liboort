#include "Pooling2DLayer.h"

namespace oort {
    Pooling2DLayer::Pooling2DLayer(const uint32_t inWidth, const uint32_t inHeight, const uint32_t channelsNum, const uint32_t filterWidth, const uint32_t filterHeight) :
    PoolingLayer(inWidth * inHeight * channelsNum, (inWidth / filterWidth) * (inHeight / filterHeight) * channelsNum, channelsNum) {}

}