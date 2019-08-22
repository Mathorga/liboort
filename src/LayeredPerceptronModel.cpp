#include "LayeredPerceptronModel.h"

namespace Oort {
    const vector_size_t LayeredPerceptronModel::DEFAULT_LAYERS_NUM = 3;
    const vector_size_t LayeredPerceptronModel::DEFAULT_OUT_LAYERS_NUM = 1;
    const vector_size_t LayeredPerceptronModel::DEFAULT_LAYER_SIZE = 3;

    LayeredPerceptronModel::LayeredPerceptronModel() {
        this->layersNum = DEFAULT_LAYERS_NUM;
        this->outputLayersNum = DEFAULT_OUT_LAYERS_NUM;
        this->layers = new Vector<Vector<Perceptron>>();

        this->createLayers(DEFAULT_LAYER_SIZE);
    }

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum) {
        this->layersNum = layersNum;
        this->outputLayersNum = DEFAULT_OUT_LAYERS_NUM;
        this->layers = new Vector<Vector<Perceptron>>();

        this->createLayers(DEFAULT_LAYER_SIZE);
    }

    LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum, vector_size_t layerSize) {
        this->layersNum = layersNum;
        this->outputLayersNum = DEFAULT_OUT_LAYERS_NUM;
        this->layers = new Vector<Vector<Perceptron>>();

        this->createLayers(layerSize);
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
        // Create layers.
        for (vector_size_t i = 0; i < this->layersNum; i++) {
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
}
