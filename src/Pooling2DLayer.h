#ifndef __POOLING2D_LAYER__
#define __POOLING2D_LAYER__

#include "PoolingLayer.h"
#include "math.h"

namespace oort {
    class Pooling2DLayer : public PoolingLayer {
    private:
        uint32_t filterWidth;
        uint32_t filterHeight;
        math::dtensor2d composedValues;
        math::dtensor2d activatedValues;

    public:
        Pooling2DLayer(const uint32_t inWidth, const uint32_t inHeight, const uint32_t channelsNum, const uint32_t filterWidth, const uint32_t filterHeight);

    };
}

#endif