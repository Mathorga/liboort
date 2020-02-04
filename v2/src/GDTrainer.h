/*
********************************************************************************
GDTrainer.h

Definition of the general class for stochastic gradient descent learning.

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __G_D_TRAINER__
#define __G_D_TRAINER__

#include "Trainer.h"

namespace oort {
    class GDTrainer : public Trainer {
    public:
        // Trains the model.
        void train();

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
