#include "SimpleBrain.h"
#include "utils.h"

SimpleBrain::SimpleBrain(uint16_t inputNum, uint16_t outputNum) {
    this->model = new Model();

    this->model->setInputNum(inputNum);
    this->model->setOutputNum(outputNum);
    this->model->setHiddenNum(0);

    this->model->setNeuronsNum(inputNum + outputNum);
    this->model->setSynapsesNum(inputNum * outputNum);

    this->learningRate = 0.2;

    this->baseWeight = 0;
    this->baseValue = 0;

    // Generate random seed.
    srand(time(NULL));

    // Neurons' allocation and initialization.
    this->model->setNeurons((Model::_Neuron *) malloc(this->model->getNeuronsNum() * sizeof(Model::_Neuron)));

    for (uint16_t i = 0; i < inputNum; i++) {
        this->model->getNeurons()[i].type = Model::typeInput;
        this->model->getNeurons()[i].value = dRandBetween(this->baseValue - 1, this->baseValue + 1);
        this->model->getNeurons()[i].error = 0;
        this->model->getNeurons()[i].enabled = true;
    }

    for (uint16_t i = inputNum; i < model->getNeuronsNum(); i++) {
        this->model->getNeurons()[i].type = Model::typeOutput;
        this->model->getNeurons()[i].value = 0;
        this->model->getNeurons()[i].error = 0;
        this->model->getNeurons()[i].enabled = true;
    }

    // Synapses' allocation and initialization.
    this->model->setSynapses((Model::_Synapse *) malloc(this->model->getSynapsesNum() * sizeof(Model::_Synapse)));
    for (uint32_t i = 0; i < this->model->getSynapsesNum(); i++) {
        this->model->getSynapses()[i].weight = this->baseWeight;//dRandBetween(this->baseWeight - 1, this->baseWeight + 1);
        this->model->getSynapses()[i].enabled = true;
    }

    // Loop through neurons to attach synapses.
    uint32_t synapsePosition = 0;
    // Inputs.
    for (uint16_t i = 0; i < inputNum; i++) {
        // Outputs.
        for (uint16_t o = inputNum; o < this->model->getNeuronsNum(); o++) {
            this->model->getSynapses()[synapsePosition].inputNeuron = i;
            this->model->getSynapses()[synapsePosition].outputNeuron = o;
            synapsePosition++;
        }
    }
}

SimpleBrain::SimpleBrain(Model *inputModel) {
    this->model = inputModel;

    //TODO Take the learning rate as an input.
    this->learningRate = 0.2;

    //TODO Remove.
    this->model->randomizeInputValues();
    this->model->randomizeSynapsesWeights();
}

void SimpleBrain::run() {
    for (uint16_t i = 0; i < this->model->getNeuronsNum(); i++) {
        if (this->model->getNeurons()[i].type == Model::typeOutput) {
            this->calculateNeuronValue(i);
        }
    }
    return;
}

void SimpleBrain::setExpectedOutput(double *expectedOutput) {
    this->expectedOutput = expectedOutput;
    printf("\n\n%f\n\n", this->expectedOutput[0]);
    return;
}

void SimpleBrain::correct() {
    // Compute the errors of the neurons of the net.
    this->computeError();

    // Adjust the synapses' weights based on the neurons' errors.
    this->adjustWeights();
}

void SimpleBrain::computeError() {
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
        // Check if the neuron is input (no need to calculate the error).
        if (this->model->getNeurons()[i].type == Model::typeInput) {
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
            }

            // If the neuron is of kind output calculate its error and delta.
            if (this->model->getNeurons()[neuronsBuffer[i]].type == Model::typeOutput) {
                this->model->getNeurons()[neuronsBuffer[i]].error = this->expectedOutput[neuronsBuffer[i] - this->model->getInputNum()] - this->model->getNeurons()[neuronsBuffer[i]].value;
            }

            // The neuron is complete, so calculate its competers' errors.
            // Calculate the sum of the weights coming to the current neuron.
            double incomingWeight = 0;
            for (uint16_t j = 0; j < this->model->getSynapsesNum(); j++) {
                if (this->model->getSynapses()[j].outputNeuron == neuronsBuffer[i]) {
                    incomingWeight += this->model->getSynapses()[j].weight;
                }
            }
            // Update the errors of the neurons that compete to the current one and correct their weights.
            // #pragma omp parallel for
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

    free(bufferHead);
    return;
}

void SimpleBrain::adjustWeights() {
    // Loop through synapses to update the weights.
    #pragma omp parallel for
    for (uint16_t i = 0; i < this->model->getSynapsesNum(); i++) {
        this->model->getSynapses()[i].weight += this->learningRate * this->model->getNeurons()[this->model->getSynapses()[i].outputNeuron].error * this->model->getNeurons()[this->model->getSynapses()[i].outputNeuron].dValue * this->model->getNeurons()[this->model->getSynapses()[i].inputNeuron].value;
    }
}

void SimpleBrain::setInput(double *input) {
    uint16_t inputPosition = 0;
    for (uint16_t i = 0; i < this->model->getNeuronsNum(); i ++) {
        if (this->model->getNeurons()[i].type == Model::typeInput) {
            this->model->getNeurons()[i].value = input[inputPosition];
            inputPosition++;
        }
    }
    return;
}

double *SimpleBrain::getOutput() {
    double *output = (double *) malloc(this->model->getOutputNum() * sizeof(double));
    uint16_t outputPosition = 0;
    for (uint16_t i = 0; i < this->model->getNeuronsNum(); i ++) {
        if (this->model->getNeurons()[i].type == Model::typeOutput) {
            output[outputPosition] = this->model->getNeurons()[i].value;
            outputPosition++;
        }
    }
    return output;
}

uint16_t SimpleBrain::getInputNum() {
    return this->model->getInputNum();
}

uint16_t SimpleBrain::getOutputNum() {
    return this->model->getOutputNum();
}

uint16_t SimpleBrain::getHiddenNum() {
    return this->model->getHiddenNum();
}

uint16_t SimpleBrain::getNeuronsNum() {
    return this->model->getNeuronsNum();
}

uint16_t SimpleBrain::getSynapsesNum() {
    return this->model->getSynapsesNum();
}

Model* SimpleBrain::getModel() {
    return this->model;
}

Model::_Neuron *SimpleBrain::getNeurons() {
    return this->model->getNeurons();
}

Model::_Synapse *SimpleBrain::getSynapses() {
    return this->model->getSynapses();
}

double SimpleBrain::calculateNeuronValue(uint16_t neuronNum) {
    // Recursion base case.
    if (this->model->getNeurons()[neuronNum].type == Model::typeInput) {
        return this->model->getNeurons()[neuronNum].value;
    }

    double value = 0;

    for (uint16_t i = 0; i < this->model->getSynapsesNum(); i++) {
        if (this->model->getSynapses()[i].enabled && this->model->getSynapses()[i].outputNeuron == neuronNum) {
            value += this->calculateNeuronValue(this->model->getSynapses()[i].inputNeuron) * this->model->getSynapses()[i].weight;
        }
    }

    this->model->getNeurons()[neuronNum].value = activate(value);
    this->model->getNeurons()[neuronNum].dValue = dActivate(value);

    return this->model->getNeurons()[neuronNum].value;
}

double SimpleBrain::activate(double input) {
    // Sigmoid function.
    return (1 / (1 + (pow(M_E, -(input)))));

    // Tanh function.
    // return tanh(input);
}

double SimpleBrain::dActivate(double input) {
    // Sigmoid derivative.
    return this->activate(input) * (1 - this->activate(input));
}

void SimpleBrain::randomlyAddSynapse() {

    return;
}

void SimpleBrain::randomlyAddNeuron() {

    return;
}

bool SimpleBrain::addSynapse(uint16_t inputNeuron, uint16_t outputNeuron) {
    // Check if synapse alredy exists.
    for (uint16_t i = 0; i < this->model->getSynapsesNum(); i++) {
        if (this->model->getSynapses()[i].inputNeuron == inputNeuron && this->model->getSynapses()[i].outputNeuron == outputNeuron) {
            return false;
        }
    }

    // Synapse doesn't alredy exist, so add it.
    this->model->setSynapsesNum(this->model->getSynapsesNum() + 1);
    uint16_t size = this->model->getSynapsesNum() * sizeof(Model::_Synapse);
    this->model->setSynapses((Model::_Synapse *) realloc(this->model->getSynapses(), size));
    this->model->getSynapses()[this->model->getSynapsesNum() - 1].inputNeuron = inputNeuron;
    this->model->getSynapses()[this->model->getSynapsesNum() - 1].outputNeuron = outputNeuron;
    this->model->getSynapses()[this->model->getSynapsesNum() - 1].weight = dRandBetween(this->baseWeight - 1, this->baseWeight + 1);
    this->model->getSynapses()[this->model->getSynapsesNum() - 1].enabled = true;
    return true;
}

bool SimpleBrain::addNeuron(uint16_t inputNeuron, uint16_t outputNeuron) {
    for (uint16_t i = 0; i < this->model->getSynapsesNum(); i++) {
        if (this->model->getSynapses()[i].inputNeuron == inputNeuron && this->model->getSynapses()[i].outputNeuron == outputNeuron) {
            // Disable the original synapse (in which to insert the neuron).
            this->model->getSynapses()[i].enabled = false;

            // Insert the new neuron.
            this->model->setHiddenNum(this->model->getHiddenNum() + 1);
            this->model->setNeuronsNum(this->model->getNeuronsNum() + 1);
            uint16_t size = this->model->getNeuronsNum() * sizeof(Model::_Neuron);
            this->model->setNeurons((Model::_Neuron *) realloc(this->model->getNeurons(), size));
            this->model->getNeurons()[this->model->getNeuronsNum() - 1].type = Model::typeHidden;
            this->model->getNeurons()[this->model->getNeuronsNum() - 1].value = 0;
            this->model->getNeurons()[this->model->getNeuronsNum() - 1].error = 0;
            this->model->getNeurons()[this->model->getNeuronsNum() - 1].enabled = true;

            // Create two new synapses around the new neuron.
            this->model->setSynapsesNum(this->model->getSynapsesNum() + 2);
            size = this->model->getSynapsesNum() * sizeof(Model::_Synapse);
            this->model->setSynapses((Model::_Synapse *) realloc(this->model->getSynapses(), size));
            this->model->getSynapses()[this->model->getSynapsesNum() - 1].inputNeuron = inputNeuron;
            this->model->getSynapses()[this->model->getSynapsesNum() - 1].outputNeuron = this->model->getNeuronsNum() - 1;
            this->model->getSynapses()[this->model->getSynapsesNum() - 1].weight = dRandBetween(this->baseWeight - 1, this->baseWeight + 1);
            this->model->getSynapses()[this->model->getSynapsesNum() - 1].enabled = true;

            this->model->getSynapses()[this->model->getSynapsesNum() - 2].inputNeuron = this->model->getNeuronsNum() - 1;
            this->model->getSynapses()[this->model->getSynapsesNum() - 2].outputNeuron = outputNeuron;
            this->model->getSynapses()[this->model->getSynapsesNum() - 2].weight = dRandBetween(this->baseWeight - 1, this->baseWeight + 1);
            this->model->getSynapses()[this->model->getSynapsesNum() - 2].enabled = true;

            return true;
        }
    }
    return false;
}

void SimpleBrain::describe() {
    this->model->describe();
}
