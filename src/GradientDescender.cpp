#include "GradientDescender.h"

namespace oort {
    void GradientDescender::run() {
        double error = 0.0;
        tensor::dtensor1d vals;
        tensor::itensor1d deps;
        tensor::dtensor1d dActivatedVals;
        tensor::dtensor1d** dOut;
        tensor::dtensor1d dIn;
        tensor::dtensor2d* dWeight;
        tensor::dtensor1d* dBias;
        tensor::dtensor1d cDOut;

        // Allocate dOut.
        dOut = (tensor::dtensor1d**) malloc(this->model->getMemLoopsNum() * sizeof(tensor::dtensor1d*));
        for (uint32_t i = 0; i < this->model->getMemLoopsNum(); i++) {
            dOut[i] = (tensor::dtensor1d*) malloc(this->model->getLayersNum() * sizeof(tensor::dtensor1d));
            for (uint32_t j = 0; j < this->model->getLayersNum(); j++) {
                tensor::alloc(&(dOut[i][j]), this->model->getLayerSize(j));
                tensor::zero(dOut[i][j]);
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
                error = tensor::prim(vals, this->knowledge.getExperience(j).getOutputs(), this->costFunction);
                printf("\n%d %d ERROR %f\n", i, j, error);

                // Calculate dOut for the last layer (i.e. output layer) based on expected output.
                tensor::der(dOut[0][this->model->getLayersNum() - 1], vals, this->knowledge.getExperience(j).getOutputs(), this->costFunction);
                // printf("\nOUT LAYER DOUT");
                // print(dOut[0][this->model->getLayersNum() - 1]);

                // Backpropagate the error.
                for (int32_t l = this->model->getLayersNum() - 1; l >= 0; l--) {
                    // Allocate delta weights.
                    dWeight = (tensor::dtensor2d*) malloc(this->model->getLayerDepsNum(l) * sizeof(tensor::dtensor2d));
                    for (uint32_t d = 0; d < this->model->getLayerDepsNum(l); d++) {
                        tensor::alloc(&(dWeight[d]),
                                    this->model->getLayerSize(l),
                                    this->model->getLayerSize(this->model->getLayerDeps(l).values[d]));
                        tensor::zero(dWeight[d]);
                    }

                    // Allocate dIn.
                    tensor::alloc(&dIn, this->model->getLayerSize(l));

                    // Allocate dActivatedVals.
                    tensor::alloc(&dActivatedVals, this->model->getLayerSize(l));

                    // Get layer dependencies.
                    deps = this->model->getLayerDeps(l);

                    // Compute dIn based on dOut.
                    tensor::der(dActivatedVals, this->model->getLayerComposedVals(l), this->model->getLayerActivation(l));
                    tensor::hmul(dIn, dActivatedVals, dOut[0][l]);

                    // Compute weight delta and apply it.
                    for (uint32_t d = 0; d < deps.width; d++) {
                        tensor::mul(dWeight[d], this->model->getLayerActivatedVals(deps.values[d]), dIn);
                        // printf("\nDWeight");
                        // print(dWeight[d]);
                        // printf("\nActivVals");
                        // print(this->model->getLayerActivatedVals(l));
                        // printf("\ndIn, %d", l);
                        // print(dIn[0][l]);

                        tensor::add(this->model->getLayerWeights(l)[d], dWeight[d]);
                    }

                    // Add up to all dOuts.
                    for (uint32_t d = 0; d < deps.width; d++) {
                        tensor::alloc(&cDOut, this->model->getLayerWeights(l)[d].height);
                        tensor::mul(cDOut, this->model->getLayerWeights(l)[d], dIn);
                        tensor::cadd(dOut[0][deps.values[d]], cDOut);
                        tensor::dealloc(cDOut);
                    }

                    // Reset vals for the next layer.
                    // tensor::copy(vals, dOut);

                    tensor::dealloc(dIn);
                    for (uint32_t d = 0; d < this->model->getLayerDepsNum(l); d++) {
                        tensor::dealloc(dWeight[d]);
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
                tensor::dealloc(dOut[i][j]);
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
    void GradientDescender::setCostFunction(tensor::DT1DBinFunc* costFunction) {
        this->costFunction = costFunction;
    }
}
