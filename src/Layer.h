/*
********************************************************************************
Layer.h

TODO

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __LAYER__
#define __LAYER__

#include "math.h"

namespace oort {
    class Layer {
    public:
        Layer(const uint32_t inSize, const uint32_t outSize);
        virtual void step(math::dtensor input) = 0;
        virtual void print() = 0;
    protected:
        uint32_t inSize;
        uint32_t outSize;
    };
}

#endif
