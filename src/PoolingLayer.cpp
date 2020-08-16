#include "PoolingLayer.h"

namespace oort {
    PoolingLayer::PoolingLayer(const uint32_t inSize, const uint32_t outSize, const uint32_t channelsNum, const PoolingFunction poolingFunction) :
    Layer(inSize, outSize) {
        // Set channels number.
        this->channelsNum = channelsNum;

        // Set pooling function.
        this->poolingFunction = poolingFunction;
    }
}