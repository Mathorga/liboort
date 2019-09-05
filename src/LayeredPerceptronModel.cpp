#include "LayeredPerceptronModel.h"

namespace Oort {
    const vector_size_t LayeredPerceptronModel::DEFAULT_LAYERS_NUM = 3;
    const vector_size_t LayeredPerceptronModel::DEFAULT_OUT_LAYERS_NUM = 1;
    const vector_size_t LayeredPerceptronModel::DEFAULT_LAYER_SIZE = 3;

    LayeredPerceptronModel::LayeredPerceptronModel() : LayeredPerceptronModel(DEFAULT_LAYERS_NUM) {}

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum) : LayeredPerceptronModel(layersNum, DEFAULT_LAYER_SIZE) {}

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum, vector_size_t layerSize) : LayeredPerceptronModel(layersNum, DEFAULT_OUT_LAYERS_NUM, layerSize) {}

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum, vector_size_t outputLayersNum, vector_size_t layerSize) {
        this->layersNum = layersNum;
        this->outputLayersNum = outputLayersNum;
        this->layers = new Vector<Vector<Perceptron>>();

        this->createLayers(layerSize);
    }

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum, vector_size_t* layerSizes) : LayeredPerceptronModel(layersNum, DEFAULT_OUT_LAYERS_NUM, layerSizes) {}

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum, vector_size_t outputLayersNum, vector_size_t* layerSizes) {
        this->layersNum = layersNum;
        this->outputLayersNum = outputLayersNum;
        this->layers = new Vector<Vector<Perceptron>>();

        this->createLayers(new Vector<vector_size_t>(layersNum, layerSizes));
    }

    LayeredPerceptronModel::LayeredPerceptronModel(Vector<vector_size_t>* layerSizes) : LayeredPerceptronModel(layerSizes, DEFAULT_OUT_LAYERS_NUM) {}

    LayeredPerceptronModel::LayeredPerceptronModel(Vector<vector_size_t>* layerSizes, vector_size_t outputLayersNum) {
        this->layersNum = layerSizes->getSize();
        this->outputLayersNum = outputLayersNum;
        this->layers = new Vector<Vector<Perceptron>>();

        this->createLayers(layerSizes);
    }

    void LayeredPerceptronModel::print() {
        printf("\n|LAYERED PERCEPTRON MODEL\n");
        for (vector_size_t i = 0; i < this->layers->getSize(); i++) {
            printf("|LAYER %d\n", i);
            for (vector_size_t j = 0; j < this->layers->getItem(i)->getSize(); j++) {
                this->layers->getItem(i)->getItem(j)->print();
            }
        }
        printf("\n");
    }

    Vector<Vector<Perceptron>>* LayeredPerceptronModel::getLayersVector() {
        return this->layers;
    }

    Vector<Perceptron>* LayeredPerceptronModel::getLayer(vector_size_t index) {
        return this->layers->getItem(index);
    }

    vector_size_t LayeredPerceptronModel::getLayersNum() {
        return this->layers->getSize();
    }

    vector_size_t LayeredPerceptronModel::getOutputLayersNum() {
        return this->outputLayersNum;
    }

    void LayeredPerceptronModel::createLayers(vector_size_t layerSize) {
        // Create layers.
        for (vector_size_t i = 0; i < this->layersNum; i++) {
            this->layers->addLast(new Vector<Perceptron>());
            // Create perceptrons in each layer.
            if (i <= 0) {
                // Input layer.
                for (vector_size_t j = 0; j < layerSize; j++) {
                    this->layers->getLast()->addLast(new Perceptron(IDX(i, j, this->layersNum), Neuron::typeInput));
                }
            } else {
                // Hidden and output layers.
                for (vector_size_t j = 0; j < layerSize; j++) {
                    this->layers->getLast()->addLast(new Perceptron(IDX(i, j, this->layersNum), i >= (this->layersNum - this->outputLayersNum) ? Neuron::typeOutput : Neuron::typeHidden));

                    // Create synapses:
                    // In order to fully connect the model, synapses are necessary between each layer, so they're
                    // created from the first non-input layer onwards.
                    for (vector_size_t k = 0; k < layerSize; k++) {
                        this->layers->getLast()->getLast()->getSynapses()->addLast(new PerceptronSynapse(this->layers->getItem(i - 1)->getItem(k), PerceptronSynapse::DEFAULT_WEIGHT));
                    }
                }
            }
        }
    }

    void LayeredPerceptronModel::createLayers(vector_size_t inputLayerSize, vector_size_t outputLayerSize, vector_size_t hiddenLayerSize) {
        // Loop for layers number to create all layers.
        for (vector_size_t i = 0; i < this->layersNum; i++) {
            // Create a single layer and add it.
            this->layers->addLast(new Vector<Perceptron>());
            // Create perceptrons in each layer.
            if (i <= 0) {
                // Input layer.
                for (vector_size_t j = 0; j < inputLayerSize; j++) {
                    this->layers->getLast()->addLast(new Perceptron(IDX(i, j, this->layersNum), Neuron::typeInput));
                }
            } else if (i >= this->layersNum - this->outputLayersNum) {
                // Output layers.
                for (vector_size_t j = 0; j < outputLayerSize; j++) {
                    this->layers->getLast()->addLast(new Perceptron(IDX(i, j, this->layersNum), Neuron::typeOutput));

                    // Create synapses:
                    // In order to fully connect the model, synapses are necessary between each layer, so they're
                    // created from the first non-input layer onwards.
                    for (vector_size_t k = 0; k < this->layers->getItem(i - 1)->getSize(); k++) {
                        this->layers->getLast()->getLast()->getSynapses()->addLast(new PerceptronSynapse(this->layers->getItem(i - 1)->getItem(k), PerceptronSynapse::DEFAULT_WEIGHT));
                    }
                }
            } else {
                // Hidden layers.
                for (vector_size_t j = 0; j < hiddenLayerSize; j++) {
                    this->layers->getLast()->addLast(new Perceptron(IDX(i, j, this->layersNum), Neuron::typeHidden));

                    // Create synapses:
                    // In order to fully connect the model, synapses are necessary between each layer, so they're
                    // created from the first non-input layer onwards.
                    for (vector_size_t k = 0; k < this->layers->getItem(i - 1)->getSize(); k++) {
                        this->layers->getLast()->getLast()->getSynapses()->addLast(new PerceptronSynapse(this->layers->getItem(i - 1)->getItem(k), PerceptronSynapse::DEFAULT_WEIGHT));
                    }
                }
            }
        }
    }

    void LayeredPerceptronModel::createLayers(Vector<vector_size_t>* layerSizes) {
        // Keep index up to date in order to set correct ids to neurons.
        vector_size_t index = 0;
        // Create layers.
        for (vector_size_t i = 0; i < this->layersNum; i++) {
            // Create a single layer and add it.
            this->layers->addLast(new Vector<Perceptron>());

            // Create perceptron in each layer.
            if (i <= 0) {
                // Input layer: only the first layer is input.
                // Loop for single layer size.
                for (vector_size_t j = 0; j < *(layerSizes->getItem(i)); j++) {
                    // Add Perceptron to layer.
                    this->layers->getLast()->addLast(new Perceptron(index, Neuron::typeInput));

                    // Update index.
                    index++;
                }
            } else {
                // Hidden and output layers.
                for (vector_size_t j = 0; j < *(layerSizes->getItem(i)); j++) {
                    this->layers->getLast()->addLast(new Perceptron(index, i >= (this->layersNum - this->outputLayersNum) ? Neuron::typeOutput : Neuron::typeInput));

                    // Create synapes:
                    // In order to fully connect the model, synapses are necessary between each layer, so they're
                    // created from the first non-input layer onwards.
                    for (vector_size_t k = 0; k < this->layers->getItem(i - 1)->getSize(); k++) {
                        this->layers->getLast()->getLast()->getSynapses()->addLast(new PerceptronSynapse(this->layers->getItem(i - 1)->getItem(k), PerceptronSynapse::DEFAULT_WEIGHT));
                    }

                    // Update index.
                    index++;
                }
            }
        }
    }
}
