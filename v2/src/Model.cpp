#include "Model.h"

namespace oort {
    const array_size_t Model::DEFAULT_LAYERS_NUM = 3;
    const array_size_t Model::DEFAULT_LAYER_SIZE = 5;
    const array_size_t Model::DEFAULT_LOOPS_NUM = 1;

    Model::Model(layers_num_t layersNum, array_size_t* layerSizes) {
        // Define layers number.
        this->layersNum = layersNum;

        // Allocate layers.
        this->layers = (struct Layer*) malloc(this->layersNum * sizeof(struct Layer));

        // Loop through layers in order to update sizes and allocate memory for
        // each one of them.
        for (uint32_t i = 0; i < this->layersNum; i++) {
            // Allocate and set target for each layer but the last one.
            // For feedforward neural networks, connections only exist between
            // each layer and the next one.
            if (i < this->layersNum - 1) {
                this->layers[i].targets = (layers_num_t*) malloc(sizeof(layers_num_t));
                this->layers[i].targets[0] = i + 1;
                this->layers[i].targetsNum = 1;
            } else {
                this->layers[i].targetsNum = 0;
            }

            // Allocate synapses.
            this->layers[i].synapseWeights = (synapse_weight_t**) malloc(this->layers[i].targetsNum * sizeof(synapse_weight_t*));
            for (uint32_t j = 0; j < this->layers[i].targetsNum; j++) {
                // The number of synapses the current layer to its jth target
                // is equal to the product between its neurons number and its
                // target's neurons number.
                this->layers[i].synapseWeights[j] = (synapse_weight_t*) malloc(this->layers[i].neuronsNum * this->layers[this->layers[i].targets[j]].neuronsNum * sizeof(synapse_weight_t));
            }

            // Set layer size.
            this->layers[i].neuronsNum = layerSizes[i];

            // Allocate neuron values.
            this->layers[i].neuronValues = (neuron_value_t*) malloc(this->layers[i].neuronsNum * sizeof(neuron_value_t));
        }
    }

    Model::Model(layers_num_t layersNum) {
        // Define layers number.
        this->layersNum = layersNum;

        // Allocate layers.
        this->layers = (struct Layer*) malloc(this->layersNum * sizeof(struct Layer));

        // Loop through layers in order to update sizes and allocate memory for
        // each one of them.
        for (uint32_t i = 0; i < this->layersNum; i++) {
            // Allocate and set target for each layer but the last one.
            // For feedforward neural networks, connections only exist between
            // each layer and the next one.
            if (i < this->layersNum - 1) {
                this->layers[i].targets = (layers_num_t*) malloc(sizeof(layers_num_t));
                this->layers[i].targets[0] = i + 1;
                this->layers[i].targetsNum = 1;
            } else {
                this->layers[i].targetsNum = 0;
            }

            // Allocate synapses.
            this->layers[i].synapseWeights = (synapse_weight_t**) malloc(this->layers[i].targetsNum * sizeof(synapse_weight_t*));
            for (uint32_t j = 0; j < this->layers[i].targetsNum; j++) {
                // The number of synapses the current layer to its jth target
                // is equal to the product between its neurons number and its
                // target's neurons number.
                this->layers[i].synapseWeights[j] = (synapse_weight_t*) malloc(this->layers[i].neuronsNum * this->layers[this->layers[i].targets[j]].neuronsNum * sizeof(synapse_weight_t));
            }

            // Set layer size.
            this->layers[i].neuronsNum = DEFAULT_LAYER_SIZE;

            // Allocate neuron values.
            this->layers[i].neuronValues = (neuron_value_t*) malloc(this->layers[i].neuronsNum * sizeof(neuron_value_t));
        }
    }

    Model::Model() : Model(DEFAULT_LAYERS_NUM) {}

    void Model::computeValue(loops_num_t loopsNum) {
        // Loop counter used to keep track of the performed loops.
        // loops_num_t loopsCount = 0;

        // Placeholder for synapses number between two layers.
        array_size_t synapsesNum = 0;

        // Placeholder for actual synapses values, after activation.
        synapse_weight_t* activatedSynapses = nullptr;

        // Temp array to store inputs to target layers.
        neuron_value_t* targetInputs = nullptr;

        // Loop through layers of the graph.
        for (array_size_t i = 0; i < this->layersNum; i++) {
            // Loop through the current layer's targets.
            for (array_size_t j = 0; j < this->layers[i].targetsNum; j++) {
                // Calculate the exact number of synapses between the current
                // layer and its current target.
                synapsesNum = this->layers[i].neuronsNum * this->layers[this->layers[i].targets[j]].neuronsNum;

                // Allocate activated synapses.
                activatedSynapses = (synapse_weight_t*) malloc(synapsesNum * sizeof(synapse_weight_t));

                // Allocate target inputs.
                targetInputs = (neuron_value_t*) malloc(this->layers[this->layers[i].targets[j]].neuronsNum * sizeof(neuron_value_t));

                // Activate synapses.
                hmatmul(activatedSynapses, this->layers[i].synapseWeights[j], this->layers[i].synapseActivations[j], synapsesNum);

                // Compute neuron values.
                matmul(targetInputs,
                       this->layers[i].neuronValues,
                       1, this->layers[i].neuronsNum,
                       activatedSynapses,
                       this->layers[i].neuronsNum, this->layers[this->layers[i].targets[j]].neuronsNum);

                sigmoidmat(this->layers[this->layers[i].targets[j]].neuronValues, targetInputs, this->layers[this->layers[i].targets[j]].neuronsNum);

                free(activatedSynapses);
            }
        }
    }

    void Model::computeValue() {
        this->computeValue(DEFAULT_LOOPS_NUM);
    }

    neuron_value_t* Model::getOutput() {
        // Return neuron values from the last layer of the graph.
        return this->layers[this->layersNum - 1].neuronValues;
    }

    array_size_t Model::getOutputSize() {
        // Return the size of the last layer of the graph.
        return this->layers[this->layersNum - 1].neuronsNum;
    }

    void Model::setInput(neuron_value_t* inputValues) {
        // Set neuron values only to the first layer of the graph.
        this->layers[0].neuronValues = inputValues;
    }

    void Model::setInput(neuron_value_t* inputValues, array_size_t inputSize) {
        // Check if the passed size is consistent with the graph size.
        if (inputSize == this->layers[0].neuronsNum) {
            // Input size is consistent, so set neuron values.
            this->layers[0].neuronValues = inputValues;
        } else {
            // Show error.
            printf("\n<Model::setInput()> Error: input size is not consistent:\nActual input size %d\nGiven input size %d\n", this->layers[0].neuronsNum, inputSize);
        }
    }
}
