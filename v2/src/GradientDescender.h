/*
********************************************************************************
GradientDescender.h

Definition of the general class for gradient descent learning.

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __GRADIENT_DESCENDER__
#define __GRADIENT_DESCENDER__

#include "Trainer.h"

namespace oort {
    class GradientDescender : public Trainer {
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
        uint32_t epochsNum;
        // Knowledge knowledge;
    };
}

#endif
