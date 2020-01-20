#include "Model.h"

namespace oort {
    const array_size_t Model::DEFAULT_LAYERS_NUM = 3;
    const array_size_t Model::DEFAULT_LAYER_SIZE = 5;
    const array_size_t Model::DEFAULT_LOOPS_NUM = 0;

    Model::Model(math::itensor2d structure) {
        // Allocate layers.
        math::alloc(&(this->layers), structure.width, structure.height);

        // Loop through mamory loops of the network in order to allocate each
        // one of them.
        for (uint32_t i = 0; i < this->layers.height; i++) {
            // Loop through layers in each mem loop.
            for (uint32_t j = 0; j < this->layers.width; j++) {
                // Allocate and set target for each layer but the last one.
                // For feedforward neural networks, connections only exist between
                // each layer and the next one.
                if (i < this->layers.width - 1) {
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].targets), 1);
                    this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[0] = i + 1;
                } else {
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].targets), 0);
                }

                // Allocate synapses and activations.
                this->layers.values[IDX2D(i, j, this->layers.width)].synapseWeights = (math::dtensor2d*) malloc(this->layers.values[IDX2D(i, j, this->layers.width)].targets.width * sizeof(math::dtensor2d));
                this->layers.values[IDX2D(i, j, this->layers.width)].synapseActivations = (math::dtensor2d*) malloc(this->layers.values[IDX2D(i, j, this->layers.width)].targets.width * sizeof(math::dtensor2d));
                for (uint32_t k = 0; k < this->layers.values[IDX2D(i, j, this->layers.width)].targets.width; k++) {
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].synapseWeights[k]), this->layers.values[this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[k]].neuronValues.width, this->layers.values[IDX2D(i, j, this->layers.width)].neuronValues.width);
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].synapseActivations[k]), this->layers.values[this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[k]].neuronValues.width, this->layers.values[IDX2D(i, j, this->layers.width)].neuronValues.width);
                }

                // Allocate neurons.
                math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].neuronValues), structure.values[IDX2D(i, j, this->layers.width)]);
            }
        }
    }

    Model::Model(math::itensor1d structure) {
        // Allocate layers.
        math::alloc(&(this->layers), structure.width, 1);

        // There is only one mem loop, so loop through its layers.
        for (uint32_t i = 0; i < this->layers.width; i++) {
            // Allocate and set target for each layer but the last one.
            // For feedforward neural networks, connections only exist between
            // each layer and the next one.
            if (i < this->layers.width - 1) {
                math::alloc(&(this->layers.values[i].targets), 1);
                this->layers.values[i].targets.values[0] = i + 1;
            } else {
                math::alloc(&(this->layers.values[i].targets), 0);
            }

            // Allocate synapses and activations.
            this->layers.values[i].synapseWeights = (math::dtensor2d*) malloc(this->layers.values[i].targets.width * sizeof(math::dtensor2d));
            this->layers.values[i].synapseActivations = (math::dtensor2d*) malloc(this->layers.values[i].targets.width * sizeof(math::dtensor2d));
            for (uint32_t k = 0; k < this->layers.values[i].targets.width; k++) {
                math::alloc(&(this->layers.values[i].synapseWeights[k]), this->layers.values[this->layers.values[i].targets.values[k]].neuronValues.width, this->layers.values[i].neuronValues.width);
                math::alloc(&(this->layers.values[i].synapseActivations[k]), this->layers.values[this->layers.values[i].targets.values[k]].neuronValues.width, this->layers.values[i].neuronValues.width);
            }

            // Allocate neurons.
            math::alloc(&(this->layers.values[i].neuronValues), structure.values[i]);
        }
    }

    Model::Model(loops_num_t memloopsNum, layers_num_t layersNum, array_size_t* layerSizes) {
        // Allocate layers.
        math::alloc(&(this->layers), layersNum, memloopsNum);

        // Loop through mamory loops of the network in order to allocate each
        // one of them.
        for (uint32_t i = 0; i < this->layers.height; i++) {
            // Loop through layers in each mem loop.
            for (uint32_t j = 0; j < this->layers.width; j++) {
                // Allocate and set target for each layer but the last one.
                // For feedforward neural networks, connections only exist between
                // each layer and the next one.
                if (i < this->layers.width - 1) {
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].targets), 1);
                    this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[0] = i + 1;
                } else {
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].targets), 0);
                }

                // Allocate synapses and activations.
                this->layers.values[IDX2D(i, j, this->layers.width)].synapseWeights = (math::dtensor2d*) malloc(this->layers.values[IDX2D(i, j, this->layers.width)].targets.width * sizeof(math::dtensor2d));
                this->layers.values[IDX2D(i, j, this->layers.width)].synapseActivations = (math::dtensor2d*) malloc(this->layers.values[IDX2D(i, j, this->layers.width)].targets.width * sizeof(math::dtensor2d));
                for (uint32_t k = 0; k < this->layers.values[IDX2D(i, j, this->layers.width)].targets.width; k++) {
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].synapseWeights[k]), this->layers.values[this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[k]].neuronValues.width, this->layers.values[IDX2D(i, j, this->layers.width)].neuronValues.width);
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].synapseActivations[k]), this->layers.values[this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[k]].neuronValues.width, this->layers.values[IDX2D(i, j, this->layers.width)].neuronValues.width);
                }

                // Allocate neurons.
                math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].neuronValues), layerSizes[IDX2D(i, j, this->layers.width)]);
            }
        }
    }

    Model::Model(layers_num_t layersNum, array_size_t* layerSizes) : Model(1, layersNum, layerSizes) {}

    Model::Model(layers_num_t layersNum) {
        // Allocate layers.
        math::alloc(&(this->layers), layersNum, 1);

        // There is only one mem loop, so loop through its layers.
        for (uint32_t i = 0; i < this->layers.width; i++) {
            // Allocate and set target for each layer but the last one.
            // For feedforward neural networks, connections only exist between
            // each layer and the next one.
            if (i < this->layers.width - 1) {
                math::alloc(&(this->layers.values[i].targets), 1);
                this->layers.values[i].targets.values[0] = i + 1;
            } else {
                math::alloc(&(this->layers.values[i].targets), 0);
            }

            // Allocate synapses and activations.
            this->layers.values[i].synapseWeights = (math::dtensor2d*) malloc(this->layers.values[i].targets.width * sizeof(math::dtensor2d));
            this->layers.values[i].synapseActivations = (math::dtensor2d*) malloc(this->layers.values[i].targets.width * sizeof(math::dtensor2d));
            for (uint32_t k = 0; k < this->layers.values[i].targets.width; k++) {
                math::alloc(&(this->layers.values[i].synapseWeights[k]), this->layers.values[this->layers.values[i].targets.values[k]].neuronValues.width, this->layers.values[i].neuronValues.width);
                math::alloc(&(this->layers.values[i].synapseActivations[k]), this->layers.values[this->layers.values[i].targets.values[k]].neuronValues.width, this->layers.values[i].neuronValues.width);
            }

            // Allocate neurons.
            math::alloc(&(this->layers.values[i].neuronValues), DEFAULT_LAYER_SIZE);
        }
    }

    Model::Model() : Model(DEFAULT_LAYERS_NUM) {}

    void Model::computeValue(loops_num_t loopsNum) {
        // Loop counter used to keep track of the performed loops.
        // loops_num_t loopsCount = 0;

        // Placeholder for actual synapses values, after activation.
        math::dtensor2d activatedSynapses;

        // Temp array to store inputs to target layers.
        math::dtensor1d targetInputs;
        math::dtensor1d activatedInputs;

        // Loop through layers of the graph.
        for (array_size_t i = 0; i < this->layersNum; i++) {
            // Loop through the current layer's targets.
            for (array_size_t j = 0; j < this->layers[i].targets.width; j++) {
                // Allocate activated synapses.
                math::alloc(&(activatedSynapses), this->layers[i].synapseWeights[j].width, this->layers[i].synapseWeights[j].height);
                math::copy(activatedSynapses, this->layers[i].synapseWeights[j]);

                // Allocate target inputs.
                math::alloc(&(targetInputs), this->layers[i].synapseWeights[j].width);
                // Allocate activated inputs.
                math::alloc(&(activatedInputs), this->layers[i].synapseWeights[j].width);

                // Activate synapses.
                math::hmul(activatedSynapses, this->layers[i].synapseWeights[j], this->layers[i].synapseActivations[j]);

                // Compute neuron values.
                math::mul(targetInputs, this->layers[i].neuronValues, activatedSynapses);

                // Activate neurons.
                math::sigmoid(activatedInputs, targetInputs);
                math::add(this->layers[this->layers[i].targets.values[j]].neuronValues, this->layers[this->layers[i].targets.values[j]].neuronValues, activatedInputs);

                math::dealloc(activatedSynapses);
                math::dealloc(targetInputs);
                math::dealloc(activatedInputs);
            }
        }
    }

    void Model::computeValue() {
        this->computeValue(DEFAULT_LOOPS_NUM);
    }

    neuron_value_t* Model::getOutput() {
        // Return neuron values from the last layer of the graph.
        return this->layers[this->layersNum - 1].neuronValues.values;
    }

    array_size_t Model::getOutputSize() {
        // Return the size of the last layer of the graph.
        return this->layers[this->layersNum - 1].neuronValues.width;
    }

    void Model::setInput(math::dtensor1d inputValues) {
        // Set neuron values only to the first layer of the graph.
        math::copy(this->layers[0].neuronValues, inputValues);
    }
}
