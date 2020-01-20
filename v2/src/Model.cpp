#include "Model.h"

namespace oort {
    const array_size_t Model::DEFAULT_LAYERS_NUM = 3;
    const array_size_t Model::DEFAULT_LAYER_SIZE = 5;
    const array_size_t Model::DEFAULT_MEM_LOOPS_NUM = 0;

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

                // Allocate neurons.
                math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].composedValues), structure.values[IDX2D(i, j, this->layers.width)]);
                math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].activatedValues), structure.values[IDX2D(i, j, this->layers.width)]);

                // Allocate synapses and activations.
                this->layers.values[IDX2D(i, j, this->layers.width)].synapseWeights = (math::dtensor2d*) malloc(this->layers.values[IDX2D(i, j, this->layers.width)].targets.width * sizeof(math::dtensor2d));
                this->layers.values[IDX2D(i, j, this->layers.width)].synapseActivations = (math::dtensor2d*) malloc(this->layers.values[IDX2D(i, j, this->layers.width)].targets.width * sizeof(math::dtensor2d));
                for (uint32_t k = 0; k < this->layers.values[IDX2D(i, j, this->layers.width)].targets.width; k++) {
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].synapseWeights[k]),
                                this->layers.values[this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[k]].composedValues.width,
                                this->layers.values[IDX2D(i, j, this->layers.width)].composedValues.width);
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].synapseActivations[k]),
                                this->layers.values[this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[k]].composedValues.width,
                                this->layers.values[IDX2D(i, j, this->layers.width)].composedValues.width);
                }
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

            // Allocate neurons.
            math::alloc(&(this->layers.values[i].composedValues), structure.values[i]);
            math::alloc(&(this->layers.values[i].activatedValues), structure.values[i]);

            // Allocate synapses and activations.
            this->layers.values[i].synapseWeights = (math::dtensor2d*) malloc(this->layers.values[i].targets.width * sizeof(math::dtensor2d));
            this->layers.values[i].synapseActivations = (math::dtensor2d*) malloc(this->layers.values[i].targets.width * sizeof(math::dtensor2d));
            for (uint32_t k = 0; k < this->layers.values[i].targets.width; k++) {
                math::alloc(&(this->layers.values[i].synapseWeights[k]),
                            this->layers.values[this->layers.values[i].targets.values[k]].composedValues.width,
                            this->layers.values[i].composedValues.width);
                math::alloc(&(this->layers.values[i].synapseActivations[k]),
                            this->layers.values[this->layers.values[i].targets.values[k]].composedValues.width,
                            this->layers.values[i].composedValues.width);
            }
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

                // Allocate neurons.
                math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].composedValues), layerSizes[IDX2D(i, j, this->layers.width)]);
                math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].activatedValues), layerSizes[IDX2D(i, j, this->layers.width)]);

                // Allocate synapses and activations.
                this->layers.values[IDX2D(i, j, this->layers.width)].synapseWeights = (math::dtensor2d*) malloc(this->layers.values[IDX2D(i, j, this->layers.width)].targets.width * sizeof(math::dtensor2d));
                this->layers.values[IDX2D(i, j, this->layers.width)].synapseActivations = (math::dtensor2d*) malloc(this->layers.values[IDX2D(i, j, this->layers.width)].targets.width * sizeof(math::dtensor2d));
                for (uint32_t k = 0; k < this->layers.values[IDX2D(i, j, this->layers.width)].targets.width; k++) {
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].synapseWeights[k]),
                                this->layers.values[this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[k]].composedValues.width,
                                this->layers.values[IDX2D(i, j, this->layers.width)].composedValues.width);
                    math::alloc(&(this->layers.values[IDX2D(i, j, this->layers.width)].synapseActivations[k]),
                                this->layers.values[this->layers.values[IDX2D(i, j, this->layers.width)].targets.values[k]].composedValues.width,
                                this->layers.values[IDX2D(i, j, this->layers.width)].composedValues.width);
                }
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

            // Allocate neurons.
            math::alloc(&(this->layers.values[i].composedValues), DEFAULT_LAYER_SIZE);
            math::alloc(&(this->layers.values[i].activatedValues), DEFAULT_LAYER_SIZE);

            // Allocate synapses and activations.
            this->layers.values[i].synapseWeights = (math::dtensor2d*) malloc(this->layers.values[i].targets.width * sizeof(math::dtensor2d));
            this->layers.values[i].synapseActivations = (math::dtensor2d*) malloc(this->layers.values[i].targets.width * sizeof(math::dtensor2d));
            for (uint32_t k = 0; k < this->layers.values[i].targets.width; k++) {
                math::alloc(&(this->layers.values[i].synapseWeights[k]),
                            this->layers.values[this->layers.values[i].targets.values[k]].composedValues.width,
                            this->layers.values[i].composedValues.width);
                math::alloc(&(this->layers.values[i].synapseActivations[k]),
                            this->layers.values[this->layers.values[i].targets.values[k]].composedValues.width,
                            this->layers.values[i].composedValues.width);
            }
        }
    }

    Model::Model() : Model(DEFAULT_LAYERS_NUM) {}

    void Model::computeValue() {
        // Placeholder for actual synapses values, after activation.
        math::dtensor2d activatedSynapses;

        // Temp array to store inputs to target layers.
        math::dtensor1d targetInputs;

        // Loop through the graph's mem loops.
        for (array_size_t i = 0; i < this->layers.height; i++) {
            // Loop through layers of the graph.
            for (array_size_t j = 0; j < this->layers.width; j++) {
                // Activate values of the current layer.
                math::sigmoid(this->layers.values[IDX2D(j, i, this->layers.width)].activatedValues,
                              this->layers.values[IDX2D(j, i, this->layers.width)].composedValues);

                // Loop through the current layer's targets.
                for (array_size_t k = 0; k < this->layers.values[IDX2D(j, i, this->layers.width)].targets.width; k++) {
                    // Allocate activated synapses.
                    math::alloc(&(activatedSynapses),
                                this->layers.values[IDX2D(j, i, this->layers.width)].synapseWeights[k].width,
                                this->layers.values[IDX2D(j, i, this->layers.width)].synapseWeights[k].height);
                    math::copy(activatedSynapses, this->layers.values[IDX2D(j, i, this->layers.width)].synapseWeights[k]);

                    // Allocate target inputs.
                    math::alloc(&(targetInputs), this->layers.values[IDX2D(j, i, this->layers.width)].synapseWeights[j].width);

                    // Activate synapses.
                    math::hmul(activatedSynapses,
                               this->layers.values[IDX2D(j, i, this->layers.width)].synapseWeights[k],
                               this->layers.values[IDX2D(j, i, this->layers.width)].synapseActivations[k]);

                    // Compute target inputs from the current layer.
                    math::mul(targetInputs, this->layers.values[IDX2D(j, i, this->layers.width)].activatedValues, activatedSynapses);

                    // Add computed values to target's composition.
                    math::add(this->layers.values[IDX2D(this->layers.values[IDX2D(j, i, this->layers.width)].targets.values[k], i, this->layers.width)].composedValues,
                              this->layers.values[IDX2D(this->layers.values[IDX2D(j, i, this->layers.width)].targets.values[k], i, this->layers.width)].composedValues,
                              targetInputs);

                    math::dealloc(activatedSynapses);
                    math::dealloc(targetInputs);
                }
            }
        }
    }

    neuron_value_t* Model::getOutput() {
        // Return neuron values from the last layer of the graph.
        return this->layers.values[IDX2D(this->layers.width - 1, this->layers.height - 1, this->layers.width)].activatedValues.values;
    }

    array_size_t Model::getOutputSize() {
        // Return the size of the last layer of the graph.
        return this->layers.values[IDX2D(this->layers.width - 1, this->layers.height - 1, this->layers.width)].activatedValues.width;
    }

    void Model::setInput(math::dtensor1d inputValues) {
        // Set neuron values only to the first layer of the graph.
        math::copy(this->layers.values[IDX2D(0, this->layers.height - 1, this->layers.width)].activatedValues, inputValues);
    }
}
