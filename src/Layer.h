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
        virtual void step(math::dtensor input) = 0;
    };
}

#endif
