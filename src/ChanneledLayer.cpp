#include "ChanneledLayer.h"

namespace oort {
    ChanneledLayer::ChanneledLayer(const uint32_t inSize, const uint32_t outSize, const uint32_t inChannelsNum, const uint32_t outChannelsNum) : Layer(inSize, outSize) {
        this->inChannelsNum = inChannelsNum;
        this->outChannelsNum = outChannelsNum;
    }
}