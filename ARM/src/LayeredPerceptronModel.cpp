#include "LayeredPerceptronModel.h"

vector_size_t LayeredPerceptronModel::defaultLayersNum = 3;
vector_size_t LayeredPerceptronModel::defaultLayerSize = 3;

LayeredPerceptronModel::LayeredPerceptronModel() {
    this->layers = new Vector<Vector<Perceptron>>();
    // Create layers.
    for (vector_size_t i = 0; i < defaultLayersNum; i++) {
        this->layers->addLast(new Vector<Perceptron>());
        // Create perceptrons.
        for (vector_size_t j = 0; i < defaultLayerSize; j++) {
            this->layers->getLast()->addLast(new Perceptron(j));
        }
    }
}

LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum) {
    //TODO
}

LayeredPerceptronModel::LayeredPerceptronModel(vector_size_t layersNum, vector_size_t layerSize) {
    //TODO
}

void LayeredPerceptronModel::print() {
    printf("\n|------------LAYERED_PERCEPTRON_MODEL------------");
    printf("|-----------------------------------------------\n");
    printf("\n");
}

Vector<Vector<Perceptron>>* LayeredPerceptronModel::getLayersVector() {
    return this->layers;
}

Vector<Perceptron>* LayeredPerceptronModel::getLayer(vector_size_t index) {
    return this->layers->getItem(index);
}
