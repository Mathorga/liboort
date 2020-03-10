#include "GradientDescender.h"

namespace oort {
    void GradientDescender::run() {
        double error = 0.0;
        math::dtensor1d vals;
        math::itensor1d deps;
        math::dtensor1d dActivatedVals;
        math::dtensor1d** dOut;
        math::dtensor1d dIn;
        math::dtensor2d* dWeight;
        math::dtensor1d* dBias;
        math::dtensor1d cDOut;

        // Allocate dOut.
        dOut = (math::dtensor1d**) malloc(this->model->getMemLoopsNum() * sizeof(math::dtensor1d*));
        for (uint32_t i = 0; i < this->model->getMemLoopsNum(); i++) {
            dOut[i] = (math::dtensor1d*) malloc(this->model->getLayersNum() * sizeof(math::dtensor1d));
            for (uint32_t j = 0; j < this->model->getLayersNum(); j++) {
                math::alloc(&(dOut[i][j]), this->model->getLayerSize(j));
                math::zero(dOut[i][j]);
            }
        }

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
                printf("\n%d %d ERROR %f\n", i, j, error);

                // Calculate dOut for the last layer (i.e. output layer) based on expected output.
                math::der(dOut[0][this->model->getLayersNum() - 1], vals, this->knowledge.getExperience(j).getOutputs(), this->costFunction);
                printf("\nOUT LAYER DOUT");
                print(dOut[0][this->model->getLayersNum() - 1]);

                // Backpropagate the error.
                for (int32_t l = this->model->getLayersNum() - 1; l >= 0; l--) {
                    // Allocate delta weights.
                    dWeight = (math::dtensor2d*) malloc(this->model->getLayerDepsNum(l) * sizeof(math::dtensor2d));
                    for (uint32_t d = 0; d < this->model->getLayerDepsNum(l); d++) {
                        math::alloc(&(dWeight[d]),
                                    this->model->getLayerSize(l),
                                    this->model->getLayerSize(this->model->getLayerDeps(l).values[d]));
                        math::zero(dWeight[d]);
                    }

                    // Allocate dIn.
                    math::alloc(&dIn, this->model->getLayerSize(l));

                    // Allocate dActivatedVals.
                    math::alloc(&dActivatedVals, this->model->getLayerSize(l));

                    // Get layer dependencies.
                    deps = this->model->getLayerDeps(l);

                    // Compute dIn based on dOut.
                    math::der(dActivatedVals, this->model->getLayerComposedVals(l), this->model->getLayerActivation(l));
                    math::hmul(dIn, dActivatedVals, dOut[0][l]);

                    // Compute weight delta and apply it.
                    for (uint32_t d = 0; d < deps.width; d++) {
                        math::mul(dWeight[d], this->model->getLayerActivatedVals(deps.values[d]), dIn);
                        printf("\nDWeight");
                        print(dWeight[d]);
                        // printf("\nActivVals");
                        // print(this->model->getLayerActivatedVals(l));
                        // printf("\ndIn, %d", l);
                        // print(dIn[0][l]);

                        math::add(this->model->getLayerWeights(l)[d], dWeight[d]);
                    }

                    // Add up to all dOuts.
                    for (uint32_t d = 0; d < deps.width; d++) {
                        math::alloc(&cDOut, this->model->getLayerWeights(l)[d].height);
                        math::mul(cDOut, this->model->getLayerWeights(l)[d], dIn);
                        math::cadd(dOut[0][deps.values[d]], cDOut);
                        math::dealloc(cDOut);
                    }

                    // Reset vals for the next layer.
                    // math::copy(vals, dOut);

                    math::dealloc(dIn);
                    for (uint32_t d = 0; d < this->model->getLayerDepsNum(l); d++) {
                        math::dealloc(dWeight[d]);
                    }
                    delete dWeight;
                }
            //
            //     // Check if batch size or knowledge size is reached. If so
            //     // update weights and biases.
            //     if (j % this->batchSize == 0 || j == this->knowledge.getExperiencesNum() - 1) {
            //         // Update weights and biases.
                // }
            }
        }

        for (uint32_t i = 0; i < this->model->getMemLoopsNum(); i++) {
            for (uint32_t j = 0; j < this->model->getLayersNum(); j++) {
                math::dealloc(dOut[i][j]);
            }
            delete dOut[i];
        }
        delete dOut;

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
    void GradientDescender::setKnowledge(Knowledge knowledge) {
        this->knowledge = knowledge;
    }
    void GradientDescender::setCostFunction(math::DT1DBinFunc* costFunction) {
        this->costFunction = costFunction;
    }
}
