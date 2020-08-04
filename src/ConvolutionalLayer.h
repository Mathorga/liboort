#ifndef __CONV_LAYER__
#define __CONV_LAYER__

#include "Layer.h"

namespace oort {
    class ConvolutionalLayer : public Layer {
    protected:
        uint32_t inChannelsNum;
        uint32_t outChannelsNum;

    public:
        ConvolutionalLayer(const uint32_t inSize, const uint32_t outSize, const uint32_t inChannelsNum, const uint32_t outChannelsNum);
    };
}

#endif
