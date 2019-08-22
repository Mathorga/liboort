#include "LayeredPerceptronNetwork.h"

namespace Oort {
    LayeredPerceptronNetwork::LayeredPerceptronNetwork() {
        this->model = nullptr;
    }

    LayeredPerceptronNetwork::LayeredPerceptronNetwork(LayeredPerceptronModel* model) {
        this->model = model;
    }

    void LayeredPerceptronNetwork::run() {
        this->computeValue();
    }

    void LayeredPerceptronNetwork::correct() {
        // Compute the errors of the neurons of the net.
        this->computeError();

        // Adjust the synapses' weights based on the neurons' errors.
        this->adjustWeights();
    }

    void LayeredPerceptronNetwork::train(Knowledge* knowledge, uint32_t iterationsNum) {
        //TODO
    }

    neuron_value_t LayeredPerceptronNetwork::activate(perceptron_input_t value) {
        // Sigmoid function.
        return (1 / (1 + (pow(M_E, -(value)))));
    }

    neuron_value_t LayeredPerceptronNetwork::dActivate(perceptron_input_t value) {
        // Sigmoid derivative function.
        return this->activate(value) * (1 - this->activate(value));
    }

    void LayeredPerceptronNetwork::print() {
        if (this->model != nullptr) {
            this->model->print();
        }
    }

    LayeredPerceptronModel* LayeredPerceptronNetwork::getModel() {
        return nullptr;
    }

    neuron_value_t* LayeredPerceptronNetwork::getOutput() {
        return nullptr;
    }

    void LayeredPerceptronNetwork::setModel(LayeredPerceptronModel* model) {
        this->model = model;
    }

    void LayeredPerceptronNetwork::setInput(neuron_value_t* input) {
        for (vector_size_t i = 0; i < this->model->getLayer(0)->getSize(); i++) {
            this->model->getLayer(0)->getItem(i)->setValue(input[i]);
        }
    }

    void LayeredPerceptronNetwork::setInput(Vector<neuron_value_t>* input) {
        for (vector_size_t i = 0; i < this->model->getLayer(0)->getSize(); i++) {
            this->model->getLayer(0)->getItem(i)->setValue(*(input->getItem(i)));
        }
    }

    void LayeredPerceptronNetwork::setExpectedOutput(neuron_value_t* expectedOutput) {

    }

    void LayeredPerceptronNetwork::computeValue() {
        neuron_value_t value = 0;

        // Loop through layers skipping the first one, which is input.
        for (vector_size_t i = 1; i < this->model->getLayersNum(); i++) {
            // Loop through neurons in each layer.
            #pragma omp parallel for
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

    void LayeredPerceptronNetwork::computeError() {

    }

    void LayeredPerceptronNetwork::adjustWeights() {

    }
}
