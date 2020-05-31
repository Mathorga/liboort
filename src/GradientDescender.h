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
#include "Knowledge.h"

namespace oort {
    class GradientDescender : public Trainer {
    public:
        // Optimizes the model.
        void run();

        // Accessors.
        double getLearningRate();
        uint32_t getBatchSize();
        uint32_t getEpochsNum();
        void setLearningRate(double learningRate);
        void setBatchSize(uint32_t batchSize);
        void setEpochsNum(uint32_t epochsNum);
        void setKnowledge(Knowledge knowledge);
        void setCostFunction(tensor::DT1DBinFunc* costFunction);

    private:
        double learningRate;
        uint32_t batchSize;
        uint32_t epochsNum;
        Knowledge knowledge;
        tensor::DT1DBinFunc* costFunction;
    };
}

#endif
