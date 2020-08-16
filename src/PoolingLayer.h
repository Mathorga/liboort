/*
********************************************************************************
PoolingLayer.h

TODO

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __POOLING_LAYER__
#define __POOLING_LAYER__

#include "Layer.h"

namespace oort {
    class PoolingLayer : public Layer {
    protected:
        enum PoolingFunction {
            MAX,
            AVG,
            MIN,
            MED
        };

        // Number of channels of the layer.
        uint32_t channelsNum;

        // Pooling function used in the layer.
        PoolingFunction poolingFunction;

    public:
        PoolingLayer(const uint32_t inSize, const uint32_t outSize, const uint32_t channelsNum, const PoolingFunction poolingFunction);
    };
}

#endif