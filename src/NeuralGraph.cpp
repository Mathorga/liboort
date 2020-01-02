#include "NeuralGraph.h"

namespace Oort {
    const array_size_t NeuralGraph::DEFAULT_LAYERS_NUM = 3;
    const array_size_t NeuralGraph::DEFAULT_LAYER_SIZE = 5;

    NeuralGraph::NeuralGraph(array_size_t layersNum, array_size_t* layerSizes) {
        // // Temp variable used to record synapses number between layers.
        // array_size_t synapsesNum = 0;

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

    NeuralGraph::NeuralGraph() {
        // // Define layers number.
        // this->layersNum = DEFAULT_LAYERS_NUM;
        //
        // // Define each layer's size and target.
        // for (uint32_t i = 0; i < this->layersNum; i++) {
        //
        //     this->layerSizes[i] = DEFAULT_LAYER_SIZE;
        // }
        //
        // // Allocate neuron values.
        // this->neuronValues = (neuron_value_t**) malloc(DEFAULT_LAYERS_NUM * sizeof(neuron_value_t*));
        // for (uint32_t i = 0; i < ) {
        //
        // }
        //
        // // Allocate synapse weights.
        // this->synapseWeights = (synapse_weight_t**) malloc(DEFAULT_LAYERS_NUM * sizeof(synapse_weight_t*));
    }


}
