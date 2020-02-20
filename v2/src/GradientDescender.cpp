#include "GradientDescender.h"

namespace oort {
    void GradientDescender::run() {
        double error = 0.0;
        math::dtensor1d vals;
        math::dtensor1d derivedVals;
        math::itensor1d deps;

        // Loop for specified epochs number.
        for (uint32_t i = 0; i < this->epochsNum; i++) {
            // Loop through knowledge data.
            for (uint32_t j = 0; j < this->knowledge.getExperiencesNum(); j++) {
                // Feed inputs to the model.
                this->model->feed(this->knowledge.getExperience(j).getInputs());

                // Run the model.
                this->model->compute();

                // Get the predicted output from the model.
                vals = this->model->getOutput();

                // Calculate the error of the model.
                error = math::prim(vals, this->knowledge.getExperience(j).getOutputs(), this->costFunction);

                // Backpropagate the error.
                for (uint32_t l = this->model->getLayersNum() - 1; l >= 0; l--) {
                    // Allocate derived values.
                    math::alloc(&derivedVals, this->model->getLayerSize(l));

                    // Get layer dependencies.
                    deps = this->model->getLayerDeps(l);

                    if (l == this->model->getLayersNum() - 1) {
                        // Compute the error partial derivative with respect to each output.
                        math::der(derivedVals, vals, this->knowledge.getExperience(j).getOutputs(), this->costFunction);
                    }

                    //TODO Loop through dependencies.
                    // for () {
                    //
                    // }

                    math::dealloc(derivedVals);
                }

                // Check if batch size or knowledge size is reached. If so
                // update weights and biases.
                if (j % this->batchSize == 0 || j == this->knowledge.getExperiencesNum() - 1) {
                    // Update weights and biases.
                }
            }
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
    uint32_t GradientDescender::getEpochsNum() {
        return this->epochsNum;
    }

    // Setters.
    void GradientDescender::setLearningRate(double learningRate) {
        this->learningRate = learningRate;
    }
    void GradientDescender::setBatchSize(uint32_t batchSize) {
        this->batchSize = batchSize;
    }
    void GradientDescender::setEpochsNum(uint32_t epochsNum) {
        this->epochsNum = epochsNum;
    }
}
