#ifndef __POOLING2D_LAYER__
#define __POOLING2D_LAYER__

#include "PoolingLayer.h"

namespace oort {
    class Pooling2DLayer : public PoolingLayer {

    private:
        uint32_t channelWidth;
        uint32_t channelHeight;
    };
}

#endif