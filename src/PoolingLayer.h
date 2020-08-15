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
        enum poolingFunction {
            MAX,
            AVG,
            MIN,
            MED
        };

        uint32_t channelsNum;

    public:
        PoolingLayer(const uint32_t inSize, const uint32_t outSize, const uint32_t channelsNum);
    };
}

#endif