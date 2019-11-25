#ifndef __PERCEPTRON_MODEL__
#define __PERCEPTRON_MODEL__

#include "Model.h"
#include "Perceptron.h"

namespace Oort {
    class PerceptronModel : public Model {
    public:
        virtual void print() = 0;

        // Getters.
        // Returns a single perceptron according to the received id.
        virtual Perceptron* getPerceptron(vector_size_t id) = 0;
        virtual Perceptron* getNeurons() = 0;
    };
}

#endif
