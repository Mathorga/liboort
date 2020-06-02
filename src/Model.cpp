#include "Model.h"

namespace oort {
    const uint32_t Model::DEFAULT_LAYERS_NUM = 0;
    const uint32_t Model::DEFAULT_LAYER_SIZE = 5;
    const double Model::DEFAULT_SYNAPSE_WEIGHT = 0.5;

    Model::Model(uint32_t layersNum, uint32_t* layerSizes){
        // Set size members.
        this->layersNum = layersNum;

        // Allocate layers.
        this->layers = (Layer*) malloc(this->layersNum * sizeof(Layer));

        // Loop through layers.
        for (uint32_t i = 0; i < this->layersNum; i++) {
            // Allocate neurons.
            math::alloc(&(this->layers[i].composedValues), layerSizes[i]);
            math::alloc(&(this->layers[i].activatedValues), layerSizes[i]);

            // Only allocate synapses for layers after the first, since the first layer has no synapses or biases coming to it.
            if (i > 0) {
                // Allocate synapses and activations.
                math::alloc(&(this->layers[i].weights),
                            this->layers[i].composedValues.width,
                            this->layers[i - 1].composedValues.width);
                // Set all synapse weights to 1.
                math::init(this->layers[i].weights, DEFAULT_SYNAPSE_WEIGHT);
                math::alloc(&(this->layers[i].weightActivations),
                            this->layers[i].composedValues.width,
                            this->layers[i - 1].composedValues.width);
                // Set all synapse activations to 1.
                math::init(this->layers[i].weightActivations, 1.0);

                // Allocate biases.
                math::alloc(&(this->layers[i].biases),
                            this->layers[i].composedValues.width);
                // Set all biases to 1.
                math::init(this->layers[i].biases, 1.0);
            }

            // Set activation function.
            this->layers[i].activationFunction = new math::Sigmoid();
        }
    }

    Model::Model(uint32_t layersNum) {
        // Set size members.
        this->layersNum = layersNum;

        // Allocate layers.
        this->layers = (Layer*) malloc(this->layersNum * sizeof(Layer));

        // Loop through layers in each mem loop.
        for (uint32_t i = 0; i < this->layersNum; i++) {
            // Allocate neurons.
            math::alloc(&(this->layers[i].composedValues), DEFAULT_LAYER_SIZE);
            math::alloc(&(this->layers[i].activatedValues), DEFAULT_LAYER_SIZE);

            // Only allocate synapses for layers after the first, since the first layer has no synapses or biases coming to it.
            if (i > 0) {
                // Allocate synapses and activations.
                math::alloc(&(this->layers[i].weights),
                            this->layers[i].composedValues.width,
                            this->layers[i - 1].composedValues.width);
                // Set all synapse weights to 1.
                math::init(this->layers[i].weights, DEFAULT_SYNAPSE_WEIGHT);
                math::alloc(&(this->layers[i].weightActivations),
                            this->layers[i].composedValues.width,
                            this->layers[i - 1].composedValues.width);
                // Set all synapse activations to 1.
                math::init(this->layers[i].weightActivations, 1.0);

                // Allocate biases.
                math::alloc(&(this->layers[i].biases),
                            this->layers[i].composedValues.width);
                // Set all biases to 1.
                math::init(this->layers[i].biases, 1.0);
            }

            // Set activation function.
            this->layers[i].activationFunction = new math::Sigmoid();
        }
    }

    Model::Model() : Model(DEFAULT_LAYERS_NUM) {}

    void Model::compute() {
        // Placeholder for actual synapses values, after activation.
        math::dtensor2d activatedSynapses;

        // Temp array to store inputs to target layers.
        math::dtensor1d inputs;

        // Loop through layers of the graph avoiding the input one.
        for (uint32_t i = 1; i < this->layersNum; i++) {
            // Clear layer's values.
            math::zero(this->layers[i].composedValues);
            math::zero(this->layers[i].activatedValues);

            // Allocate activated synapses.
            math::alloc(&(activatedSynapses),
                        this->layers[i].weights.width,
                        this->layers[i].weights.height);
            math::copy(activatedSynapses, this->layers[i].weights);

            // Allocate inputs.
            math::alloc(&(inputs), this->layers[i].weights.width);

            // Activate synapses.
            math::hmul(activatedSynapses,
                       this->layers[i].weights,
                       this->layers[i].weightActivations);

            // Compute inputs to the current layer.
            math::mul(inputs, this->layers[i - 1].activatedValues, activatedSynapses);
            // Add biases from the current dependency.
            math::add(inputs, this->layers[i].biases);

            // Add computed values to the layer composition.
            math::add(this->layers[i].composedValues,
                      inputs);

            math::dealloc(activatedSynapses);
            math::dealloc(inputs);

            // Activate values of the current layer if not input.
            math::prim(this->layers[i].activatedValues,
                       this->layers[i].composedValues,
                       this->layers[i].activationFunction);
        }
    }

    void Model::feed(math::dtensor1d inputValues) {
        // Set neuron values only to the first layer of the graph.
        math::copy(this->layers[0].activatedValues, inputValues);
    }

    void Model::setActivation(math::DUnFunc* function) {
        for (uint32_t i = 0; i < this->layersNum; i++) {
            this->layers[i].activationFunction = function;
        }
    }

    math::dtensor1d Model::getOutput() {
        // Return neuron values from the last layer of the graph.
        return this->layers[this->layersNum - 1].activatedValues;
    }

    uint32_t Model::getOutputSize() {
        // Return the size of the last layer of the graph.
        return this->layers[this->layersNum - 1].activatedValues.width;
    }

    uint32_t Model::getLayersNum() {
        return this->layersNum;
    }

    uint32_t Model::getLayerSize(uint32_t index) {
        uint32_t layerSize = 0;

        if (index <= this->layersNum) {
            layerSize = this->layers[index].activatedValues.width;
        }

        return layerSize;
    }

    math::dtensor1d Model::getLayerComposedVals(uint32_t index) {
        math::dtensor1d layerVals;

        if (index <= this->layersNum) {
            layerVals = this->layers[index].composedValues;
        }

        return layerVals;
    }

    math::dtensor1d Model::getLayerActivatedVals(uint32_t index) {
        math::dtensor1d layerVals;

        if (index <= this->layersNum) {
            layerVals = this->layers[index].activatedValues;
        }

        return layerVals;
    }

    math::dtensor2d Model::getLayerWeights(uint32_t index) {
        math::dtensor2d layerWeights;

        if (index <= this->layersNum) {
            layerWeights = this->layers[index].weights;
        }

        return layerWeights;
    }

    math::dtensor1d Model::getLayerBiases(uint32_t index) {
        math::dtensor1d layerBiases;

        if (index <= this->layersNum) {
            layerBiases = this->layers[index].biases;
        }

        return layerBiases;
    }

    math::DUnFunc* Model::getLayerActivation(uint32_t index) {
        math::DUnFunc* layerActivation;

        if (index <= this->layersNum) {
            layerActivation = this->layers[index].activationFunction;
        }

        return layerActivation;
    }
}
