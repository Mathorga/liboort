#include "NeuralGraph.h"

namespace Oort {
    const array_size_t NeuralGraph::DEFAULT_LAYERS_NUM = 3;
    const array_size_t NeuralGraph::DEFAULT_LAYER_SIZE = 5;

    NeuralGraph::NeuralGraph(array_size_t layersNum, array_size_t* layerSizes) {
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
                this->layers[i].targets = (layer_id_t*) malloc(sizeof(layer_id_t));
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

    NeuralGraph::NeuralGraph(array_size_t layersNum) {
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
                this->layers[i].targets = (layer_id_t*) malloc(sizeof(layer_id_t));
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

    NeuralGraph::NeuralGraph() : NeuralGraph(DEFAULT_LAYERS_NUM) {}

    neuron_value_t* NeuralGraph::getOutput() {
        // Return neuron values from the last layer of the graph.
        return this->layers[this->layersNum - 1].neuronValues;
    }

    array_size_t NeuralGraph::getOutputSize() {
        // Return the size of the last layer of the graph.
        return this->layers[this->layersNum - 1].neuronsNum;
    }

    void NeuralGraph::setInput(neuron_value_t* inputValues) {
        // Set neuron values only to the first layer of the graph.
        this->layers[0].neuronValues = inputValues;
    }

    void NeuralGraph::setInput(neuron_value_t* inputValues, array_size_t inputSize) {
        // Check if the passed size is consistent with the graph size.
        if (inputSize == this->layers[0].neuronsNum) {
            // Input size is consistent, so set neuron values.
            this->layers[0].neuronValues = inputValues;
        } else {
            // Show error.
            printf("\n<NeuralGraph::setInput()> Error: input size is not consistent:\nActual input size %d\nGiven input size %d\n", this->layers[0].neuronsNum, inputSize);
        }
    }
}
