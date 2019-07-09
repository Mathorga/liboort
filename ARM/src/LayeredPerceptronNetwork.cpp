#include "LayeredPerceptronNetwork.h"

LayeredPerceptronNetwork::LayeredPerceptronNetwork() {

}

void LayeredPerceptronNetwork::run() {

}

void LayeredPerceptronNetwork::computeValue() {
    neuron_value_t value = 0;

    // Loop through layers skipping the first one, which is input.
    for (vector_size_t i = 1; i < this->model->getLayersNum(); i++) {
        // Loop through neurons in each layer.
        for (vector_size_t j = 0; j < this->model->getLayer(i)->getSize(); j++) {
            value = 0;

            // Compute the value of the single neuron based on all its inputs.
            // For each neuron in the layer, loop through all of the synapses coming to it:
            // Combination.
            for (vector_size_t k = 0; k < this->model->getLayer(i)->getItem(j)->getSynapses()->getSize(); k++) {
                value += this->model->getLayer(i)->getItem(j)->getSynapse(k)->getWeight() * this->model->getLayer(i)->getItem(j)->getSynapse(k)->getInputNeuron()->getValue();
            }

            // Activation.
            this->model->getLayer(i)->getItem(j)->setValue(this->activate(value));

            // Derivative activation.
            this->model->getLayer(i)->getItem(j)->setDValue(this->dActivate(value));
        }
    }
}
