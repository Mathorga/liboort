#include "LayeredPerceptronModel.h"

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
    printf("\n|------------LAYERED_PERCEPTRON_MODEL------------\n");
    for (vector_size_t i = 0; i < this->layers->getSize(); i++) {
        printf("Layer %d\n", i);
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

void LayeredPerceptronModel::createLayers(vector_size_t layerSize) {
    // Create layers.
    for (vector_size_t i = 0; i < this->layersNum; i++) {
        this->layers->addLast(new Vector<Perceptron>());
        // Create perceptrons.
        if (i == 0) {
            // Input layer.
            for (vector_size_t j = 0; j < layerSize; j++) {
                this->layers->getLast()->addLast(new Perceptron(IDX(i, j, this->layersNum), Neuron::typeInput));
            }
        } else if (i >= (this->layersNum - this->outputLayersNum)) {
            // Output layer.
            for (vector_size_t j = 0; j < layerSize; j++) {
                this->layers->getLast()->addLast(new Perceptron(IDX(i, j, this->layersNum), Neuron::typeOutput));
            }
        } else {
            for (vector_size_t j = 0; j < layerSize; j++) {
                // Hidden layer.
                this->layers->getLast()->addLast(new Perceptron(IDX(i, j, this->layersNum), Neuron::typeHidden));
            }
        }
    }
}
