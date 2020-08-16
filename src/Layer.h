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
    protected:
        uint32_t inSize;
        uint32_t outSize;

    public:
        Layer(const uint32_t inSize, const uint32_t outSize);

        // Performs a single step through the whole layer.
        // @param input The input tensor to process (from the previous layer or network input).
        virtual void step(math::dtensor input) = 0;
        virtual void backprop() = 0;
        virtual void print() = 0;

        uint32_t getInSize();
        uint32_t getOutSize();
    };
}

#endif
