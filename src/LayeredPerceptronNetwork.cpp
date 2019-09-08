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
        // Check if knowledge is consistent with model.
        if (this->model->getInputsNum() == knowledge->getInputsNum() && this->model->getOutputsNum() == knowledge->getOutputsNum()) {
            // Run the whole training iterationsNum times.
            for (uint32_t i = 0; i < iterationsNum; i++) {
                // Loop through knowledge experiences.
                for (uint32_t j = 0; j < knowledge->getExperiencesNum(); j++) {
                    // Set model inputs based on experience inputs.
                    this->setInput(knowledge->getExperience(j)->getInputs());

                    // Set expected outputs based on experience outputs.
                    this->setExpectedOutput(knowledge->getExperience(j)->getOutputs());

                    // Run the network in order to get outputs.
                    this->run();

                    // Correct weights based on the output.
                    this->correct();
                }
            }
        } else {
            // Knowledge size is not consistent with model size.
            printf("\n<LayeredPerceptronNetwork::train()> Error: knowledge size not consistent\n");
        }
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
        // Be careful: the array passed as an input could be shorter than the size of the output layer.
        // If array size is not exactly right or not known, then use:
        // <void setExpectedOutput(Vector<Vector<neuron_value_t>>* expectedOutput)>

        // Loop through neurons in the output layer.
        for (vector_size_t i = 0; i < this->model->getOutputLayer()->getSize(); i++) {
            // Set expected output.
            this->model->getOutputLayer()->getItem(i)->setExpectedOutput(expectedOutput[i]);
        }
    }

    bool LayeredPerceptronNetwork::setExpectedOutput(Vector<neuron_value_t>* expectedOutput) {
        bool success = false;

        // Check if passed vector size is consistent with total output neurons number.
        if (this->model->getOutputsNum() == expectedOutput->getSize()) {
            // Everything is consistent, so set expected output.
            for (vector_size_t i = 0; i < this->model->getOutputLayer()->getSize(); i++) {
                this->model->getOutputLayer()->getItem(i)->setExpectedOutput(*(expectedOutput->getItem(i)));
            }
            success = true;
        } else {
            // Expected outputs number size is not consistent with output neurons number.
            printf("\n<LayeredPerceptronNetwork::setExpectedOutput()> Error: expected outputs number is not consistent with output neurons number\n");
            success = false;
        }

        return success;
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
        //TODO
        // Store the current neuron in a variable, so that it doesn't have to be retrieved multiple times.
        Perceptron* currentNeuron = nullptr;

        // Store incoming weignt to use it on hidden neuron error computation.
        synapse_weight_t incomingWeight = 0;

        // Compute errors for output layer.
        for (vector_size_t i = 0; i < this->model->getOutputLayer()->getSize(); i++) {
            // Get the current neuron.
            currentNeuron = this->model->getOutputLayer()->getItem(i);

            // Compute error.
            currentNeuron->setError(currentNeuron->getExpectedOutput() - currentNeuron->getValue());
        }

        // Compute errors starting from the last not-output layer.
        for (vector_size_t i = this->model->getLayersNum() - 2; i < ) {
            // Loop through neurons of each layer.
            for (vector_size_t j = 0; j < this->model->getLayer(i)->getSize(); j++) {
                // Get the current neuron.
                currentNeuron = this->model->getLayer(i)->getItem(j);

                // Reset incoming weight.
                incomingWeight = 0;

                // Loop through all synapes coming to the current neuron to calculate the incoming weight.
                for (vector_size_t k = 0; k < currentNeuron->getSynapsesNum(); k++) {
                    // Add up to current weight.
                    incomingWeight += currentNeuron->getSynapse(k)->getWeight();
                }
            }
        }
    }

    void LayeredPerceptronNetwork::adjustWeights() {

    }
}
