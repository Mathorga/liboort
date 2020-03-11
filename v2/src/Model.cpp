#include "Model.h"

namespace oort {
    const uint32_t Model::DEFAULT_LAYERS_NUM = 3;
    const uint32_t Model::DEFAULT_LAYER_SIZE = 5;
    const uint32_t Model::DEFAULT_MEM_LOOPS_NUM = 0;
    const double Model::DEFAULT_SYNAPSE_WEIGHT = 0.5;

    Model::Model(uint32_t memLoopsNum, uint32_t layersNum, uint32_t* layerSizes) {
        // Set size members.
        this->memLoopsNum = memLoopsNum;
        this->layersNum = layersNum;

        // Allocate layers.
        this->layers = (Layer**) malloc(this->memLoopsNum * sizeof(Layer*));
        for (uint32_t i = 0; i < this->memLoopsNum; i++) {
            this->layers[i] = (Layer*) malloc(this->layersNum * sizeof(Layer));
        }

        // Loop through memory loops of the network in order to allocate each
        // one of them.
        for (uint32_t i = 0; i < this->memLoopsNum; i++) {
            // Loop through layers in each mem loop.
            for (uint32_t j = 0; j < this->layersNum; j++) {
                // Allocate and set dependency for each layer but the first one.
                // For feedforward neural networks, connections only exist
                // between each layer and the next one.
                if (j <= 0) {
                    math::alloc(&(this->layers[i][j].dependencies), 0);
                } else {
                    math::alloc(&(this->layers[i][j].dependencies), 1);
                    math::init(this->layers[i][j].dependencies, j - 1);
                }

                // Allocate neurons.
                math::alloc(&(this->layers[i][j].composedValues), layerSizes[j]);
                math::alloc(&(this->layers[i][j].activatedValues), layerSizes[j]);

                // Allocate synapses and activations.
                this->layers[i][j].weights = (math::dtensor2d*) malloc(this->layers[i][j].dependencies.width * sizeof(math::dtensor2d));
                this->layers[i][j].weightActivations = (math::dtensor2d*) malloc(this->layers[i][j].dependencies.width * sizeof(math::dtensor2d));
                for (uint32_t k = 0; k < this->layers[i][j].dependencies.width; k++) {
                    math::alloc(&(this->layers[i][j].weights[k]),
                                this->layers[i][j].composedValues.width,
                                this->layers[i][this->layers[i][j].dependencies.values[k]].composedValues.width);
                    // Set all synapse weights to 1.
                    math::init(this->layers[i][j].weights[k], DEFAULT_SYNAPSE_WEIGHT);
                    math::alloc(&(this->layers[i][j].weightActivations[k]),
                                this->layers[i][j].composedValues.width,
                                this->layers[i][this->layers[i][j].dependencies.values[k]].composedValues.width);
                    // Set all synapse activations to 1.
                    math::init(this->layers[i][j].weightActivations[k], 1.0);
                }

                // Allocate biases.
                this->layers[i][j].biases = (math::dtensor1d*) malloc(this->layers[i][j].dependencies.width * sizeof(math::dtensor1d));
                for (uint32_t k = 0; k < this->layers[i][j].dependencies.width; k++) {
                    math::alloc(&(this->layers[i][j].biases[k]),
                                this->layers[i][j].composedValues.width);
                    // Set all biases to 1.
                    math::init(this->layers[i][j].biases[k], 1.0);
                }

                // Set activation function.
                this->layers[i][j].activationFunction = new math::Sigmoid();
            }
        }
    }

    Model::Model(uint32_t layersNum, uint32_t* layerSizes) : Model(1, layersNum, layerSizes) {}

    Model::Model(uint32_t layersNum) {
        // Set size members.
        this->memLoopsNum = 1;
        this->layersNum = layersNum;

        // Allocate layers.
        this->layers = (Layer**) malloc(this->memLoopsNum * sizeof(Layer*));
        for (uint32_t i = 0; i < this->memLoopsNum; i++) {
            this->layers[i] = (Layer*) malloc(this->layersNum * sizeof(Layer));
        }

        // Loop through memory loops of the network in order to allocate each
        // one of them.
        for (uint32_t i = 0; i < this->memLoopsNum; i++) {
            // Loop through layers in each mem loop.
            for (uint32_t j = 0; j < this->layersNum; j++) {
                // Allocate and set dependency for each layer but the first one.
                // For feedforward neural networks, connections only exist
                // between each layer and the next one.
                if (i <= 0) {
                    math::alloc(&(this->layers[i][j].dependencies), 0);
                } else {
                    math::alloc(&(this->layers[i][j].dependencies), 1);
                    this->layers[i][j].dependencies.values[0] = i - 1;
                }

                // Allocate neurons.
                math::alloc(&(this->layers[i][j].composedValues), DEFAULT_LAYER_SIZE);
                math::alloc(&(this->layers[i][j].activatedValues), DEFAULT_LAYER_SIZE);

                // Allocate synapses and activations.
                this->layers[i][j].weights = (math::dtensor2d*) malloc(this->layers[i][j].dependencies.width * sizeof(math::dtensor2d));
                this->layers[i][j].weightActivations = (math::dtensor2d*) malloc(this->layers[i][j].dependencies.width * sizeof(math::dtensor2d));
                for (uint32_t k = 0; k < this->layers[i][j].dependencies.width; k++) {
                    math::alloc(&(this->layers[i][j].weights[k]),
                                this->layers[i][j].composedValues.width,
                                this->layers[i][this->layers[i][j].dependencies.values[k]].composedValues.width);
                    // Set all synapse weights to 1.
                    math::init(this->layers[i][j].weights[k], DEFAULT_SYNAPSE_WEIGHT);
                    math::alloc(&(this->layers[i][j].weightActivations[k]),
                                this->layers[i][j].composedValues.width,
                                this->layers[i][this->layers[i][j].dependencies.values[k]].composedValues.width);
                    // Set all synapse activations to 1.
                    math::init(this->layers[i][j].weightActivations[k], 1.0);
                }

                // Allocate biases.
                this->layers[i][j].biases = (math::dtensor1d*) malloc(this->layers[i][j].dependencies.width * sizeof(math::dtensor1d));
                for (uint32_t k = 0; k < this->layers[i][j].dependencies.width; k++) {
                    math::alloc(&(this->layers[i][j].biases[k]),
                                this->layers[i][j].composedValues.width);
                    // Set all biases to 1.
                    math::init(this->layers[i][j].biases[k], 1.0);
                }

                // Set activation function.
                this->layers[i][j].activationFunction = new math::Sigmoid();
            }
        }
    }

    Model::Model() : Model(DEFAULT_LAYERS_NUM) {}

    void Model::compute() {
        // Placeholder for actual synapses values, after activation.
        math::dtensor2d activatedSynapses;

        // Temp array to store inputs to target layers.
        math::dtensor1d inputs;

        // Loop through the graph's mem loops.
        for (uint32_t i = 0; i < this->memLoopsNum; i++) {
            // Loop through layers of the graph avoiding the input one.
            for (uint32_t j = 1; j < this->layersNum; j++) {
                // Clear layer's values.
                math::zero(this->layers[i][j].composedValues);
                math::zero(this->layers[i][j].activatedValues);

                // Loop through the current layer's targets.
                for (uint32_t k = 0; k < this->layers[i][j].dependencies.width; k++) {
                    // Allocate activated synapses.
                    math::alloc(&(activatedSynapses),
                                this->layers[i][j].weights[k].width,
                                this->layers[i][j].weights[k].height);
                    math::copy(activatedSynapses, this->layers[i][j].weights[k]);

                    // Allocate inputs.
                    math::alloc(&(inputs), this->layers[i][j].weights[k].width);

                    // Activate synapses.
                    math::hmul(activatedSynapses,
                               this->layers[i][j].weights[k],
                               this->layers[i][j].weightActivations[k]);

                    // Compute inputs to the current layer.
                    // Check if the current dependency is recurrent (i.e. it
                    // comes from the current layer or one that comes after it).
                    if (this->layers[i][j].dependencies.values[k] >= j) {
                        // The dependency is recurrent, so take values from the
                        // mem loop before the current one, if there is one.
                        if (i > 0) {
                            math::mul(inputs, this->layers[i][this->layers[i][j].dependencies.values[IDX((k - 1), this->memLoopsNum)]].activatedValues, activatedSynapses);
                            // Add biases from the current dependency.
                            math::add(inputs, inputs, this->layers[i][j].biases[k]);
                        } else {
                            // The current mem loop is the first one, so unset
                            // the inputs.
                            math::zero(inputs);
                        }
                    } else {
                        // The dependency is not recurrent, so take values from
                        // the current mem loop.
                        math::mul(inputs, this->layers[i][this->layers[i][j].dependencies.values[k]].activatedValues, activatedSynapses);
                        // Add biases from the current dependency.
                        math::add(inputs, this->layers[i][j].biases[k]);
                    }

                    // Add computed values to the layer composition.
                    math::add(this->layers[i][j].composedValues,
                              inputs);

                    math::dealloc(activatedSynapses);
                    math::dealloc(inputs);
                }

                // Activate values of the current layer if not input.
                math::prim(this->layers[i][j].activatedValues,
                           this->layers[i][j].composedValues,
                           this->layers[i][j].activationFunction);
            }
        }
    }

    void Model::feed(math::dtensor1d inputValues) {
        // Shift mem loops to the left in order to make space for a new one.
        // The oldest one is removed.
        this->shift();

        // Set neuron values only to the first layer of the graph.
        math::copy(this->layers[this->memLoopsNum - 1][0].activatedValues, inputValues);
    }

    void Model::setActivation(math::DUnFunc* function) {
        for (uint32_t i = 0; i < this->memLoopsNum; i++) {
            for (uint32_t j = 0; j < this->layersNum; j++) {
                this->layers[i][j].activationFunction = function;
            }
        }
    }

    math::dtensor1d Model::getOutput() {
        // Return neuron values from the last layer of the graph.
        return this->layers[this->memLoopsNum - 1][this->layersNum - 1].activatedValues;
    }

    uint32_t Model::getOutputSize() {
        // Return the size of the last layer of the graph.
        return this->layers[this->memLoopsNum - 1][this->layersNum - 1].activatedValues.width;
    }

    uint32_t Model::getMemLoopsNum() {
        return this->memLoopsNum;
    }

    uint32_t Model::getLayersNum() {
        return this->layersNum;
    }

    uint32_t Model::getLayerSize(uint32_t index) {
        uint32_t layerSize = 0;

        if (index <= this->layersNum) {
            layerSize = this->layers[0][index].activatedValues.width;
        }

        return layerSize;
    }

    math::itensor1d Model::getLayerDeps(uint32_t index) {
        math::itensor1d layerDeps;

        if (index <= this->layersNum) {
            layerDeps = this->layers[0][index].dependencies;
        }

        return layerDeps;
    }

    math::dtensor1d Model::getLayerComposedVals(uint32_t index) {
        math::dtensor1d layerVals;

        if (index <= this->layersNum) {
            layerVals = this->layers[0][index].composedValues;
        }

        return layerVals;
    }

    math::dtensor1d Model::getLayerActivatedVals(uint32_t index) {
        math::dtensor1d layerVals;

        if (index <= this->layersNum) {
            layerVals = this->layers[0][index].activatedValues;
        }

        return layerVals;
    }

    math::dtensor2d* Model::getLayerWeights(uint32_t index) {
        math::dtensor2d* layerWeights;

        if (index <= this->layersNum) {
            layerWeights = this->layers[0][index].weights;
        }

        return layerWeights;
    }

    math::dtensor1d* Model::getLayerBiases(uint32_t index) {
        math::dtensor1d* layerBiases;

        if (index <= this->layersNum) {
            layerBiases = this->layers[0][index].biases;
        }

        return layerBiases;
    }

    uint32_t Model::getLayerDepsNum(uint32_t index) {
        uint32_t layerDepsNum;

        if (index <= this->layersNum) {
            layerDepsNum = this->layers[0][index].dependencies.width;
        }

        return layerDepsNum;
    }

    math::DUnFunc* Model::getLayerActivation(uint32_t index) {
        math::DUnFunc* layerActivation;

        if (index <= this->layersNum) {
            layerActivation = this->layers[0][index].activationFunction;
        }

        return layerActivation;
    }

    void Model::shift() {
        for (uint32_t i = 1; i < this->memLoopsNum; i++) {
            this->layers[i - 1] = this->layers[i];
            if (i == this->memLoopsNum - 1) {
                for (uint32_t j = 0; j < this->layersNum; j++) {
                    math::zero(this->layers[i][j].composedValues);
                }
            }
        }
    }
}
