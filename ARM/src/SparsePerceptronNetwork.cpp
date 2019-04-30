#include "SparsePerceptronNetwork.h"

SparsePerceptronNetwork::SparsePerceptronNetwork() {

}

SparsePerceptronNetwork::SparsePerceptronNetwork(SparsePerceptronModel* model) {
    this->model = model;
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
        if (neuronsBuffer[i]->type == Neuron::typeInput) {
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
                    value += neuronsBuffer[i]->getSynapses()[j]->weight * neuronsBuffer[i]->getSynapses()[j]->getInputNeuron()->getValue();
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
    uint16_t size = this->model->getNeuronsNum();
    uint16_t pos = 0;
    uint16_t *bufferHead = (uint16_t *) malloc(size * sizeof(uint16_t));
    uint16_t *neuronsBuffer = bufferHead;

    // Initialize the buffer.
    for (uint16_t i = 0; i < size; i++) {
        neuronsBuffer[i] = i;
    }

    // Compute errors based on the expected output.
    for (uint16_t i = 0; i < size; i++) {
        start:
        // Check if the neuron is input (no need to calculate the error).
        if (this->model->getNeurons()[i].type == SimpleModel::typeInput) {
            // Remove the neuron.
            pos++;
        } else {
            // Check if the neuron is complete (i.e. it doesn't compete to any neuron in the rest of the buffer).
            // Loop through synapses coming from current neuron.
            for (uint16_t j = 0; j < this->model->getSynapsesNum(); j++) {
                if (this->model->getSynapses()[j].inputNeuron == neuronsBuffer[i]) {
                    // Loop through neurons coming next.
                    for (uint16_t k = pos; k < size; k ++) {
                        if (this->model->getSynapses()[j].outputNeuron == neuronsBuffer[k]) {
                            goto incomplete;
                        }
                    }
                }
            }
            if (false) {
                incomplete:
                // The neuron is incomplete, so put it at the end of the buffer.
                uint16_t neuron = neuronsBuffer[i];
                for (uint16_t j = pos + 1; j < size; j++) {
                    neuronsBuffer[j - 1] = neuronsBuffer[j];
                }
                neuronsBuffer[size - 1] = neuron;

                // Skip increment.
                goto start;
            } else {

                // If the neuron is of kind output calculate its error.
                if (this->model->getNeurons()[neuronsBuffer[i]].type == SimpleModel::typeOutput) {
                    this->model->getNeurons()[neuronsBuffer[i]].error = this->expectedOutput[neuronsBuffer[i] - this->model->getInputNum()] - this->model->getNeurons()[neuronsBuffer[i]].value;
                }

                // The neuron is complete, so calculate its competers' errors.
                // Calculate the sum of the weights coming to the current neuron.
                float incomingWeight = 0;
                for (uint16_t j = 0; j < this->model->getSynapsesNum(); j++) {
                    if (this->model->getSynapses()[j].outputNeuron == neuronsBuffer[i]) {
                        incomingWeight += this->model->getSynapses()[j].weight;
                    }
                }
                // Update the errors of the neurons that compete to the current one and correct their weights.
                #pragma omp parallel for
                for (uint16_t j = 0; j < this->model->getSynapsesNum(); j++) {
                    if (this->model->getSynapses()[j].outputNeuron == neuronsBuffer[i]) {
                        // Compute the partial error.
                        this->model->getNeurons()[this->model->getSynapses()[j].inputNeuron].error += this->model->getNeurons()[neuronsBuffer[i]].error * (this->model->getSynapses()[j].weight / incomingWeight);
                    }
                }
                // Remove the neuron from the buffer.
                pos++;
            }
        }
    }

    free(bufferHead);
    return;
}
