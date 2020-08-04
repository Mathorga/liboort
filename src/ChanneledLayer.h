#ifndef __CHANNELED_LAYER__
#define __CHANNELED_LAYER__

#include "Layer.h"

namespace oort {
    class ChanneledLayer : public Layer {
    public:
        ChanneledLayer(const uint32_t inSize, const uint32_t outSize, const uint32_t inChannelsNum, const uint32_t outChannelsNum);
    protected:
        uint32_t inChannelsNum;
        uint32_t outChannelsNum;
    };
}

#endif