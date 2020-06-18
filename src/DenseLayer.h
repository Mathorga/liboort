/*
********************************************************************************
DenseLayer.h

TODO

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __DENSE_LAYER__
#define __DENSE_LAYER__

#include "Layer.h"

namespace oort {
    class DenseLayer : public Layer {
    public:
        DenseLayer(const uint32_t inSize, const uint32_t outSize);
        void step(math::dtensor input);
    private:
        math::dtensor2d weight;
        math::dtensor1d bias;
        math::dtensor1d composedValues;
        math::dtensor1d activatedValues;
    };
}

#endif
