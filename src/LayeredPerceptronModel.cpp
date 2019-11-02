#include "LayeredPerceptronModel.h"

namespace Oort {
    const vector_size_t LayeredPerceptronModel::DEFAULT_LAYERS_NUM = 3;
    const vector_size_t LayeredPerceptronModel::DEFAULT_LAYER_SIZE = 3;

    LayeredPerceptronModel::LayeredPerceptronModel() : LayeredPerceptronModel(DEFAULT_LAYERS_NUM) {}

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum) : LayeredPerceptronModel(layersNum, DEFAULT_LAYER_SIZE) {}

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum, vector_size_t layerSize) {
        this->layersNum = layersNum;
        this->layers = new Vector<Vector<Perceptron>>();

        this->createLayers(layerSize);
    }

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum, vector_size_t* layerSizes) {
        this->layersNum = layersNum;
        this->layers = new Vector<Vector<Perceptron>>();

        this->createLayers(new Vector<vector_size_t>(layersNum, layerSizes));
    }

    LayeredPerceptronModel::LayeredPerceptronModel(Vector<vector_size_t>* layerSizes) {
        this->layersNum = layerSizes->getSize();
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

    Vector<Perceptron>* LayeredPerceptronModel::getInputLayer() {
        return this->layers->getFirst();
    }

    Vector<Perceptron>* LayeredPerceptronModel::getOutputLayer() {
        return this->layers->getLast();
    }

    Vector<Perceptron>* LayeredPerceptronModel::getHiddenLayer(vector_size_t index) {
        return this->layers->getItem(index + 1);
    }

    vector_size_t LayeredPerceptronModel::getLayersNum() {
        return this->layers->getSize();
    }

    Perceptron* LayeredPerceptronModel::getPerceptron(vector_size_t id) {
        // Perceptron* result = nullptr;
        //
        // for (vector_size_t i = 0; i < this->neuronsNum; i++) {
        //     if (this->perceptrons->getItem(i)->getId() == id) {
        //         result = this->perceptrons->getItem(i);
        //         break;
        //     }
        // }
        // return result;
    }

    Perceptron* LayeredPerceptronModel::getNeurons() {
        Perceptron* result = (Perceptron*) malloc(this->neuronsNum * sizeof(Perceptron));
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
                    this->layers->getLast()->addLast(new Perceptron(IDX(i, j, this->layersNum), i >= (this->layersNum - 1) ? Neuron::typeOutput : Neuron::typeHidden));

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
                    this->layers->getLast()->addLast(new Perceptron(index, i >= (this->layersNum - 1) ? Neuron::typeOutput : Neuron::typeHidden));

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
