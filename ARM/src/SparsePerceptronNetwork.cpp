#include "SparsePerceptronNetwork.h"

SparsePerceptronNetwork::SparsePerceptronNetwork() {
    this->baseWeight = 0;
    this->baseValue = 0;
    this->learningRate = 0;
    // this->expectedOutput = (neuron_value_t*) malloc(this->model->getOutputsNum() * sizeof(neuron_value_t));
}

SparsePerceptronNetwork::SparsePerceptronNetwork(neurons_num_t inputsNum, neurons_num_t outputsNum) {
    this->baseWeight = 0;
    this->baseValue = 0;
    this->learningRate = 0;
    this->model = new SparsePerceptronModel(inputsNum, outputsNum);
}

SparsePerceptronNetwork::SparsePerceptronNetwork(SparsePerceptronModel* model) {
    this->baseWeight = 0;
    this->baseValue = 0;
    this->learningRate = 0;
    this->model = model;
}

void SparsePerceptronNetwork::run() {
    this->computeValue();
}

void SparsePerceptronNetwork::correct() {

}

void SparsePerceptronNetwork::computeValue() {
    neurons_num_t size = this->model->getNeuronsNum();
    neurons_num_t pos = 0;
    // Create a buffer containing all neurons' addresses, so that it can be rearranged however needed.
    Perceptron** bufferHead = (Perceptron**) malloc(size * sizeof(Perceptron*));
    Perceptron** neuronsBuffer = bufferHead;
    neuron_value_t value = 0;

    // Initialize the buffer.
    for (neurons_num_t i = 0; i < size; i++) {
        neuronsBuffer[i] = &(this->model->getNeurons()[i]);
    }

    // Compute values.
    for (neurons_num_t i = 0; i < size; i++) {
        start:
        // Check if the neuron is input (no need to calculate the value).
        if (neuronsBuffer[i]->getType() == Neuron::typeInput) {
            // Remove the neuron.
            pos++;
        } else {
            // Check if the neuron is complete (i.e. it doesn't depend on any neuron in the rest of the buffer).
            // Loop through synapses going to current neuron.
            for (synapses_num_t j = 0; j < neuronsBuffer[i]->getSynapsesNum(); j++) {
                // Loop through neurons coming next.
                for (neurons_num_t k = pos; k < size; k ++) {
                    if (neuronsBuffer[i]->getSynapses()[j]->getInputNeuron() == neuronsBuffer[k]) {
                        goto incomplete;
                    }
                }
            }

            if (false) {
                incomplete:
                // The neuron is incomplete, so put it at the end of the buffer.
                Perceptron* neuron = neuronsBuffer[i];
                for (neurons_num_t j = pos + 1; j < size; j++) {
                    neuronsBuffer[j - 1] = neuronsBuffer[j];
                }
                neuronsBuffer[size - 1] = neuron;

                // Skip increment.
                goto start;
            } else {
                // The neuron is complete, so calculate its value based on its competers':
                // Combination.
                value = 0;
                for (synapses_num_t j = 0; j < neuronsBuffer[i]->getSynapsesNum(); j++) {
                    value += neuronsBuffer[i]->getSynapses()[j]->getWeight() * neuronsBuffer[i]->getSynapses()[j]->getInputNeuron()->getValue();
                }

                // Activation.
                neuronsBuffer[i]->setValue(this->activate(value));

                // Derivative activation.
                neuronsBuffer[i]->setDValue(this->dActivate(value));

                // Remove the neuron from the buffer.
                pos++;
            }
        }
    }

    free(bufferHead);
    return;
}

void SparsePerceptronNetwork::computeError() {
    neurons_num_t size = this->model->getNeuronsNum();
    neurons_num_t pos = 0;
    // Create a buffer containing all neurons' addresses, so that it can be rearranged however needed.
    Perceptron** bufferHead = (Perceptron**) malloc(size * sizeof(Perceptron*));
    Perceptron** neuronsBuffer = bufferHead;

    // Initialize the buffer.
    for (neurons_num_t i = 0; i < size; i++) {
        neuronsBuffer[i] = &(this->model->getNeurons()[i]);
    }

    // Compute errors based on the expected output.
    for (neurons_num_t i = 0; i < size; i++) {
        start:
        // Check if the neuron is input (no need to calculate the error).
        if (neuronsBuffer[i]->getType() == Neuron::typeInput) {
            // Remove the neuron.
            pos++;
        } else {
            // Check if the neuron is complete (i.e. it doesn't compete to any neuron in the rest of the buffer).
            // Loop through synapses coming from current neuron.
            for (synapses_num_t j = 0; j < neuronsBuffer[i]->getSynapsesNum(); j++) {
                // Loop through neurons coming next.
                for (neurons_num_t k = pos; k < size; k ++) {
                    if (neuronsBuffer[i]->getSynapses()[j]->getInputNeuron() == neuronsBuffer[k]) {
                        goto incomplete;
                    }
                }
            }
            if (false) {
                incomplete:
                // The neuron is incomplete, so put it at the end of the buffer.
                Perceptron* neuron = neuronsBuffer[i];
                for (neurons_num_t j = pos + 1; j < size; j++) {
                    neuronsBuffer[j - 1] = neuronsBuffer[j];
                }
                neuronsBuffer[size - 1] = neuron;

                // Skip increment.
                goto start;
            } else {
                // If the neuron is of kind output calculate its error.
                if (neuronsBuffer[i]->getType() == Neuron::typeOutput) {
                    neuronsBuffer[i]->setError(neuronsBuffer[i]->getExpectedOutput() - neuronsBuffer[i]->getValue());
                }

                // The neuron is complete, so calculate its competers' errors.
                // Calculate the sum of the weights coming to the current neuron.
                synapse_weight_t incomingWeight = 0;
                for (synapses_num_t j = 0; j < neuronsBuffer[i]->getSynapsesNum(); j++) {
                    incomingWeight += neuronsBuffer[i]->getSynapses()[j]->getWeight();
                }
                // Update the errors of the neurons that compete to the current one and correct their weights.
                #pragma omp parallel for
                for (synapses_num_t j = 0; j < neuronsBuffer[i]->getSynapsesNum(); j++) {
                    // Compute the partial error.
                    ((Perceptron*) (neuronsBuffer[i]->getSynapses()[j]->getInputNeuron()))->addError(neuronsBuffer[i]->getError() * (neuronsBuffer[i]->getSynapses()[j]->getWeight() / incomingWeight));
                }
                // Remove the neuron from the buffer.
                pos++;
            }
        }
    }

    free(bufferHead);
    return;
}

neuron_value_t SparsePerceptronNetwork::activate(neuron_value_t value) {
    //TODO
    return value;
}

neuron_value_t SparsePerceptronNetwork::dActivate(neuron_value_t value) {
    //TODO
    return value;
}

void SparsePerceptronNetwork::print() {
    ((SparsePerceptronModel*) this->model)->print();
}

SparsePerceptronModel* SparsePerceptronNetwork::getModel() {
    return this->model;
}

void SparsePerceptronNetwork::setExpectedOutput(neuron_value_t* expectedOutput) {
    for (neurons_num_t i = 0, j = 0; i < this->model->getNeuronsNum(); i++) {
        if (this->model->getNeurons()[i].getType() == Neuron::typeOutput) {
            ((Perceptron*) &(this->model->getNeurons()[i]))->setExpectedOutput(expectedOutput[j]);
            j++;
        }
    }
}
