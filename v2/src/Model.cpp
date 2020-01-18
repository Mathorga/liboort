#include "Model.h"

namespace oort {
    const array_size_t Model::DEFAULT_LAYERS_NUM = 3;
    const array_size_t Model::DEFAULT_LAYER_SIZE = 5;
    const array_size_t Model::DEFAULT_LOOPS_NUM = 1;

    Model::Model(math::dtensor1d layerSizes) {
        // Define layers number.
        this->layersNum = layerSizes.width;

        // Allocate layers.
        this->layers = (Layer*) malloc(this->layersNum * sizeof(Layer));

        // Loop through layers in order to update sizes and allocate memory for
        // each one of them.
        for (uint32_t i = 0; i < this->layersNum; i++) {
            // Allocate and set target for each layer but the last one.
            // For feedforward neural networks, connections only exist between
            // each layer and the next one.
            if (i < this->layersNum - 1) {
                math::alloc(&(this->layers[i].targets), 1);
                this->layers[i].targets.values[0] = i + 1;
            } else {
                math::alloc(&(this->layers[i].targets), 0);
            }

            // Allocate synapses and activations.
            this->layers[i].synapseWeights = (math::dtensor2d*) malloc(this->layers[i].targets.width * sizeof(math::dtensor2d));
            this->layers[i].synapseActivations = (math::dtensor2d*) malloc(this->layers[i].targets.width * sizeof(math::dtensor2d));
            for (uint32_t j = 0; j < this->layers[i].targets.width; j++) {
                math::alloc(&(this->layers[i].synapseWeights[j]), this->layers[this->layers[i].targets.values[j]].neuronValues.width, this->layers[i].neuronValues.width);
                math::alloc(&(this->layers[i].synapseActivations[j]), this->layers[this->layers[i].targets.values[j]].neuronValues.width, this->layers[i].neuronValues.width);
            }

            // Set layer size.
            math::alloc(&(this->layers[i].neuronValues), layerSizes.values[i]);
        }
    }

    Model::Model(layers_num_t layersNum, array_size_t* layerSizes) {
        // Define layers number.
        this->layersNum = layersNum;

        // Allocate layers.
        this->layers = (Layer*) malloc(this->layersNum * sizeof(Layer));

        // Loop through layers in order to update sizes and allocate memory for
        // each one of them.
        for (uint32_t i = 0; i < this->layersNum; i++) {
            // Allocate and set target for each layer but the last one.
            // For feedforward neural networks, connections only exist between
            // each layer and the next one.
            if (i < this->layersNum - 1) {
                math::alloc(&(this->layers[i].targets), 1);
                this->layers[i].targets.values[0] = i + 1;
            } else {
                math::alloc(&(this->layers[i].targets), 0);
            }

            // Allocate synapses and activations.
            this->layers[i].synapseWeights = (math::dtensor2d*) malloc(this->layers[i].targets.width * sizeof(math::dtensor2d));
            this->layers[i].synapseActivations = (math::dtensor2d*) malloc(this->layers[i].targets.width * sizeof(math::dtensor2d));
            for (uint32_t j = 0; j < this->layers[i].targets.width; j++) {
                math::alloc(&(this->layers[i].synapseWeights[j]), this->layers[this->layers[i].targets.values[j]].neuronValues.width, this->layers[i].neuronValues.width);
                math::alloc(&(this->layers[i].synapseActivations[j]), this->layers[this->layers[i].targets.values[j]].neuronValues.width, this->layers[i].neuronValues.width);
            }

            // Set layer size.
            math::alloc(&(this->layers[i].neuronValues), layerSizes[i]);
        }
    }

    Model::Model(layers_num_t layersNum) {
        // Define layers number.
        this->layersNum = layersNum;

        // Allocate layers.
        this->layers = (Layer*) malloc(this->layersNum * sizeof(Layer));

        // Loop through layers in order to update sizes and allocate memory for
        // each one of them.
        for (uint32_t i = 0; i < this->layersNum; i++) {
            // Allocate and set target for each layer but the last one.
            // For feedforward neural networks, connections only exist between
            // each layer and the next one.
            if (i < this->layersNum - 1) {
                math::alloc(&(this->layers[i].targets), 1);
                this->layers[i].targets.values[0] = i + 1;
            } else {
                math::alloc(&(this->layers[i].targets), 0);
            }

            // Allocate synapses.
            this->layers[i].synapseWeights = (math::dtensor2d*) malloc(this->layers[i].targets.width * sizeof(math::dtensor2d));
            for (uint32_t j = 0; j < this->layers[i].targets.width; j++) {
                math::alloc(&(this->layers[i].synapseWeights[j]), this->layers[this->layers[i].targets.values[j]].neuronValues.width, this->layers[i].neuronValues.width);
            }

            // Set layer size.
            math::alloc(&(this->layers[i].neuronValues), DEFAULT_LAYER_SIZE);
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

        // Loop through layers of the graph.
        for (array_size_t i = 0; i < this->layersNum; i++) {
            // Loop through the current layer's targets.
            for (array_size_t j = 0; j < this->layers[i].targets.width; j++) {
                // Allocate activated synapses.
                math::alloc(&(activatedSynapses), this->layers[i].synapseWeights[j].width, this->layers[i].synapseWeights[j].height);
                math::copy(activatedSynapses, this->layers[i].synapseWeights[j]);

                // Allocate target inputs.
                math::alloc(&(targetInputs), this->layers[i].synapseWeights[j].width);

                // Activate synapses.
                math::hmul(activatedSynapses, this->layers[i].synapseWeights[j], this->layers[i].synapseActivations[j]);

                // Compute neuron values.
                math::mul(targetInputs, this->layers[i].neuronValues, activatedSynapses);

                // Activate neurons.
                math::sigmoid(this->layers[this->layers[i].targets.values[j]].neuronValues, targetInputs);

                math::dealloc(activatedSynapses);
                math::dealloc(targetInputs);
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
