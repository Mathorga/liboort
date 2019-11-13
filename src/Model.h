#ifndef __MODEL__
#define __MODEL__

#include "Neuron.h"
#include "utils.h"
#include "Vector.h"

// #define vector_size_t uint32_t

namespace Oort {
    class Model {
    public:
        virtual void print() = 0;
        void computeNeuronsNum();

        // Getters.
        vector_size_t getInputsNum();
        vector_size_t getOutputsNum();
        vector_size_t getHiddensNum();
        vector_size_t getNeuronsNum();

        // Setters.
        void setInputsNum(vector_size_t inputsNum);
        void setOutputsNum(vector_size_t outputsNum);
        void setHiddensNum(vector_size_t hiddensNum);
        void setNeuronsNum(vector_size_t neuronsNum);

    protected:
        // Number of input neurons.
        vector_size_t inputsNum;
        // Number of output neurons.
        vector_size_t outputsNum;
        // Number of hidden neurons.
        vector_size_t hiddensNum;
        // Total number of neurons.
        vector_size_t neuronsNum;
    };
}

#endif
