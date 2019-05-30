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

    this->model = new SparsePerceptronModel(inputsNum, outputsNum, true);

    // Calculate the learning rate based on the number of neurons:
    // the greater the number of neurons, the lower the learning rate.
    this->learningRate = 1 / (float) this->model->getNeuronsNum();
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
    // Compute the errors of the neurons of the net.
    this->computeError();

    // Adjust the synapses' weights based on the neurons' errors.
    this->adjustWeights();
}

void SparsePerceptronNetwork::computeValue() {
    neurons_num_t size = this->model->getNeuronsNum();
    neurons_num_t pos = 0;
    // Create a buffer containing all neurons' addresses, so that it can be rearranged however needed.
    Perceptron** bufferHead = (Perceptron**) malloc(size * sizeof(Perceptron*));
    Perceptron** neuronsBuffer = bufferHead;
    perceptron_input_t value = 0;

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
            for (vector_size_t j = 0; j < neuronsBuffer[i]->getSynapses()->getSize(); j++) {
                // Loop through neurons coming next.
                for (neurons_num_t k = pos; k < size; k ++) {
                    if (neuronsBuffer[i]->getSynapses()->getItems()[j].getInputNeuron() == neuronsBuffer[k]) {
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
                for (vector_size_t j = 0; j < neuronsBuffer[i]->getSynapses()->getSize(); j++) {
                    value += neuronsBuffer[i]->getSynapses()->getItems()[j].getWeight() * neuronsBuffer[i]->getSynapses()->getItems()[j].getInputNeuron()->getValue();
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
            for (vector_size_t j = 0; j < neuronsBuffer[i]->getSynapsesNum(); j++) {
                // Loop through neurons coming next.
                for (neurons_num_t k = pos; k < size; k ++) {
                    if (neuronsBuffer[i]->getSynapses()->getItems()[j].getInputNeuron() == neuronsBuffer[k]) {
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
                for (vector_size_t j = 0; j < neuronsBuffer[i]->getSynapsesNum(); j++) {
                    incomingWeight += neuronsBuffer[i]->getSynapses()->getItems()[j].getWeight();
                }
                // Update the errors of the neurons that compete to the current one and correct their weights.
                #pragma omp parallel for
                for (vector_size_t j = 0; j < neuronsBuffer[i]->getSynapsesNum(); j++) {
                    // Compute the partial error.
                    ((Perceptron*) (neuronsBuffer[i]->getSynapses()->getItems()[j].getInputNeuron()))->addError(neuronsBuffer[i]->getError() * (neuronsBuffer[i]->getSynapses()->getItems()[j].getWeight() / incomingWeight));
                }
                // Remove the neuron from the buffer.
                pos++;
            }
        }
    }

    free(bufferHead);
    return;
}

void SparsePerceptronNetwork::adjustWeights() {
    float dWeight;

    // Loop through synapses to update the weights.
    for (vector_size_t i = 0; i < this->model->getNeuronsNum(); i++) {
        for (vector_size_t j = 0; j < this->model->getNeuron(i)->getSynapsesNum(); j++) {
            // Calculate the weight delta.
            // dWeight = this->learningRate * this->model->getNeuron(i)->getError() * this->model->getNeuron(i)->getSynapses()->getItems()[j].getInputNeuron()->getDValue() * this->model->getNeuron(i)->getSynapses()->getItems()[j].getInputNeuron()->getValue();

            // Calculate the custom weight delta.
            dWeight = this->learningRate * this->model->getNeuron(i)->getError() * this->model->getNeuron(i)->getSynapses()->getItems()[j].getInputNeuron()->getValue();

            // Apply the delta weight.
            this->model->getNeuron(i)->getSynapses()->getItems()[j].setWeight(this->model->getNeuron(i)->getSynapses()->getItems()[j].getWeight() + dWeight);
        }
    }


    // #pragma omp parallel for
    // for (uint16_t i = 0; i < this->model->getSynapsesNum(); i++) {
    //     // Apply the delta rule.
    //     // this->model->getSynapses()[i].weight += this->learningRate * this->model->getNeurons()[this->model->getSynapses()[i].outputNeuron].error * this->model->getNeurons()[this->model->getSynapses()[i].outputNeuron].dValue * this->model->getNeurons()[this->model->getSynapses()[i].inputNeuron].value;
    //     // Apply the customized delta rule.
    //     this->model->getSynapses()[i].weight += this->learningRate * this->model->getNeurons()[this->model->getSynapses()[i].outputNeuron].error * this->model->getNeurons()[this->model->getSynapses()[i].inputNeuron].value;
    // }
}

neuron_value_t SparsePerceptronNetwork::activate(perceptron_input_t value) {
    // Sigmoid function.
    return (1 / (1 + (pow(M_E, -(value)))));
}

neuron_value_t SparsePerceptronNetwork::dActivate(perceptron_input_t value) {
    // Sigmoid derivative function.
    return this->activate(value) * (1 - this->activate(value));
}

void SparsePerceptronNetwork::print() {
    this->model->print();
}

SparsePerceptronModel* SparsePerceptronNetwork::getModel() {
    return this->model;
}

neuron_value_t* SparsePerceptronNetwork::getOutput() {
    neuron_value_t* out = (neuron_value_t*) malloc(this->model->getOutputsNum() * sizeof(neuron_value_t));
    neurons_num_t index = 0;

    for (neurons_num_t i = 0; i < this->model->getNeuronsNum(); i++) {
        if (this->model->getNeuron(i)->getType() == Neuron::typeOutput) {
            out[index] = this->model->getNeuron(i)->getValue();
            index++;
        }
    }

    return out;
}

void SparsePerceptronNetwork::setExpectedOutput(neuron_value_t* expectedOutput) {
    for (neurons_num_t i = 0, j = 0; i < this->model->getNeuronsNum(); i++) {
        if (this->model->getNeuron(i)->getType() == Neuron::typeOutput) {
            ((Perceptron*) &(this->model->getNeurons()[i]))->setExpectedOutput(expectedOutput[j]);
            j++;
        }
    }
}
