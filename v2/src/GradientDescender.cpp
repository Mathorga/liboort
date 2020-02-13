#include "GradientDescender.h"

namespace oort {
    void GradientDescender::run() {
        // Loop for specified epochs number.
        for (uint32_t i = 0; i < this->epochsNum; i++) {
            //TODO Loop through knowledge data.

        }
        return;
    }

    // Getters.
    double GradientDescender::getLearningRate() {
        return this->learningRate;
    }
    uint32_t GradientDescender::getBatchSize() {
        return this->batchSize;
    }

    // Setters.
    void GradientDescender::setLearningRate(double learningRate) {
        this->learningRate = learningRate;
    }
    void GradientDescender::setBatchSize(uint32_t batchSize) {
        this->batchSize = batchSize;
    }
}
