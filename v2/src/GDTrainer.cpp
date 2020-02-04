#include "GDTrainer.h"

namespace oort {
    void GDTrainer::train() {
        //TODO
        return;
    }

    // Getters.
    double GDTrainer::getLearningRate() {
        return this->learningRate;
    }
    uint32_t GDTrainer::getBatchSize() {
        return this->batchSize;
    }

    // Setters.
    void GDTrainer::setLearningRate(double learningRate) {
        this->learningRate = learningRate;
    }
    void GDTrainer::setBatchSize(uint32_t batchSize) {
        this->batchSize = batchSize;
    }
}
