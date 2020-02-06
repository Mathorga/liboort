#include "GDOptimizer.h"

namespace oort {
    void GDOptimizer::run() {
        //TODO
        return;
    }

    // Getters.
    double GDOptimizer::getLearningRate() {
        return this->learningRate;
    }
    uint32_t GDOptimizer::getBatchSize() {
        return this->batchSize;
    }

    // Setters.
    void GDOptimizer::setLearningRate(double learningRate) {
        this->learningRate = learningRate;
    }
    void GDOptimizer::setBatchSize(uint32_t batchSize) {
        this->batchSize = batchSize;
    }
}
