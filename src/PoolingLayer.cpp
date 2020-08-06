#include "PoolingLayer.h"

namespace oort {
    PoolingLayer::PoolingLayer(const uint32_t inSize, const uint32_t outSize, const uint32_t channelsNum) :
    Layer(inSize, outSize) {
        // Set channels number.
        this->channelsNum = channelsNum;
    }
}