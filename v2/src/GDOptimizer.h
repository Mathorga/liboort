/*
********************************************************************************
GDOptimizer.h

Definition of the general class for stochastic gradient descent learning.

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __G_D_OPTIMIZER__
#define __G_D_OPTIMIZER__

#include "Optimizer.h"

namespace oort {
    class GDOptimizer : public Optimizer {
    public:
        // Optimizes the model.
        void run();

        // Getters.
        double getLearningRate();
        uint32_t getBatchSize();

        // Setters.
        void setLearningRate(double learningRate);
        void setBatchSize(uint32_t batchSize);

    private:
        double learningRate;
        uint32_t batchSize;
    };
}

#endif
