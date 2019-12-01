#ifndef __NEURAL_NETWORK__
#define __NEURAL_NETWORK__

// #include "Model.h"
#include "Knowledge.h"
#include "utils.h"

namespace Oort {
    #define learning_rate_t double
    #define momentum_t double

    class NeuralNetwork {
    public:
        // Execute one iteration of the net.
        virtual void run() = 0;
        virtual void correct() = 0;
        virtual void train(Knowledge* knowledge, uint32_t iterationsNum) = 0;
    };
}

#endif
