#ifndef __NEURAL_NETWORK__
#define __NEURAL_NETWORK__

#include "Model.h"
#include "utils.h"

#define learning_rate_t float

namespace Oort {
    class NeuralNetwork {
    public:
        // Execute one iteration of the net.
        virtual void run() = 0;
        virtual void correct() = 0;
    };
}

#endif
