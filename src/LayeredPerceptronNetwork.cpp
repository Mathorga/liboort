#include "LayeredPerceptronNetwork.h"

namespace Oort {
    LayeredPerceptronNetwork::LayeredPerceptronNetwork() {
        this->model = nullptr;
        // this->error = 0.0;
    }

    LayeredPerceptronNetwork::LayeredPerceptronNetwork(LayeredPerceptronModel* model) {
        this->model = model;
        // this->error = 0.0;

        // Calculate the learning rate based on the number of neurons:
        // the greater the number of neurons, the lower the learning rate.
        this->learningRate = 1 / (float) this->model->getNeuronsNum();
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
        return this->model;
    }

    neuron_value_t* LayeredPerceptronNetwork::getOutput() {
        neuron_value_t* result = (neuron_value_t*) malloc(this->model->getOutputsNum());

        // Populate the result.
        for (vector_size_t i = 0; i < this->model->getOutputsNum(); i++) {
            result[i] = this->model->getOutputLayer()->getItem(i)->getValue();
        }

        return result;
    }

    void LayeredPerceptronNetwork::setModel(LayeredPerceptronModel* model) {
        this->model = model;

        // Update the learning rate according to the new model's neurons number.
        this->learningRate = 1 / (float) this->model->getNeuronsNum();
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
        // Store the current neuron so that it doesn't have to be retrieved multiple times.
        Perceptron* currentNeuron;
        neuron_value_t value = 0;

        // Loop through layers skipping the first one, which is input.
        for (vector_size_t i = 1; i < this->model->getLayersNum(); i++) {
            // Loop through neurons in each layer.
            // #pragma omp parallel for
            for (vector_size_t j = 0; j < this->model->getLayer(i)->getSize(); j++) {
                // Get the current neuron.
                currentNeuron = this->model->getLayer(i)->getItem(j);

                // Reset value in order not to have it summed up.
                value = 0;

                // Compute the value of the single neuron based on all its inputs.
                // For each neuron in the layer, loop through all of the synapses coming to it:
                // Combination.
                for (vector_size_t k = 0; k < currentNeuron->getSynapses()->getSize(); k++) {
                    value += currentNeuron->getSynapse(k)->getWeight() * currentNeuron->getSynapse(k)->getInputNeuron()->getValue();
                }

                // Activation.
                currentNeuron->setValue(this->activate(value));

                // Derivative activation.
                currentNeuron->setDValue(this->dActivate(value));

                // Reset dInput and dOutput.
                currentNeuron->setDInput(0.0);
                currentNeuron->setDOutput(0.0);
            }
        }
    }

    void LayeredPerceptronNetwork::computeError() {
        // The error is calculated backwards, because for each neuron, error needs to take into account every error of
        // every neuron the current one is connected to; all af this in relation to every other neuron connected to
        // every one of those.

        // Store the current neuron in a variable, so that it doesn't have to be retrieved multiple times.
        Perceptron* currentNeuron = nullptr;

        // Compute errors starting from the last layer, excluding the input, because inputs do not have an error.
        for (vector_size_t i = this->model->getLayersNum() - 1; i > 0; i--) {

            // Loop through neurons of each layer.
            for (vector_size_t j = 0; j < this->model->getLayer(i)->getSize(); j++) {
                // Get the current neuron.
                currentNeuron = this->model->getLayer(i)->getItem(j);

                // If output layer, then directly calculate the error.
                if (i >= this->model->getLayersNum() - 1) {
                    // Compute error.
                    currentNeuron->setDOutput(currentNeuron->getValue() - currentNeuron->getExpectedOutput());
                    // printf("\ndOutput %f\n", currentNeuron->getDOutput());
                }

                currentNeuron->setDInput(currentNeuron->getDValue() * currentNeuron->getDOutput());

                // For each neuron connected to the current one, add to its error the weighted sum between all the
                // weights coming to the current.
                for (vector_size_t k = 0; k < currentNeuron->getSynapsesNum(); k++) {
                    // currentNeuron->getSynapse(k)->getInputNeuron()->addError((currentNeuron->getError() * currentNeuron->getSynapse(k)->getWeight()) / incomingWeight);

                    // Calculate the dWeight of the current synapse.
                    currentNeuron->getSynapse(k)->setDWeight(currentNeuron->getSynapse(k)->getInputNeuron()->getValue() * currentNeuron->getDInput());

                    // Update the synapse's input neuron's dOutput.
                    currentNeuron->getSynapse(k)->getInputNeuron()->setDOutput(currentNeuron->getSynapse(k)->getInputNeuron()->getDOutput() + (currentNeuron->getSynapse(k)->getWeight() * currentNeuron->getDInput()));
                    // printf("\ndOutput ++ %f\n", currentNeuron->getSynapse(k)->getInputNeuron()->getDOutput());

                    // Update the synapses' input neuron's dInput.
                    // currentNeuron->setDInput(currentNeuron->getDValue() + currentNeuron->getDOutput());

                    // // Check if last neuron of the layer:
                    // // the last neuron of each layer completes the error for all neurons of the layer that comes before
                    // // its own, so the global error of the layer before can be updated as well.
                    // if (j >= this->model->getLayer(i)->getSize() - 1) {
                    //     // Update layer error.
                    //     layerError += currentNeuron->getSynapse(k)->getInputNeuron()->getError();
                    // }
                }

                // // Only update the layer error if last neuron of the current layer.
                // if (j >= this->model->getLayer(i)->getSize() - 1) {
                //     // Set layer error.
                //     this->errors->replaceAt(layerError, i - 1);
                // }
            }
        }
    }

    void LayeredPerceptronNetwork::adjustWeights() {
        // Store the current synapse for simplicity.
        PerceptronSynapse* currentSynapse = nullptr;

        // Loop through layers of the model.
        for (vector_size_t i = 0; i < this->model->getLayersNum(); i++) {
            // Loop through neurons in each layer.
            for (vector_size_t j = 0; j < this->model->getLayer(i)->getSize(); j++) {
                // Loop through synapses in each neuron.
                for (vector_size_t k = 0; k < this->model->getLayer(i)->getItem(j)->getSynapsesNum(); k++) {
                    currentSynapse = this->model->getLayer(i)->getItem(j)->getSynapse(k);

                    // Update the actual synapse weight.
                    currentSynapse->setWeight(currentSynapse->getWeight() - this->learningRate * currentSynapse->getDWeight());
                }
            }
        }
    }

    // void LayeredPerceptronNetwork::adjustWeights() {
    //     // Store the current neuron, so that it doesn't have to be retrieved multiple times.
    //     Perceptron* currentNeuron = nullptr;
    //
    //     // Store the delta weight in order to keep things clean.
    //     synapse_weight_t dWeight = 0.0;
    //
    //     // Loop through layers of the model starting from the first non-input.
    //     for (vector_size_t i = 1; i < this->model->getLayersNum(); i++) {
    //         // Loop through neurons in each layer.
    //         for (vector_size_t j = 0; j < this->model->getLayer(i)->getSize(); j++) {
    //             // Get current neuron.
    //             currentNeuron = this->model->getLayer(i)->getItem(j);
    //
    //             // Loop through all synapses of every neuron.
    //             for (vector_size_t k = 0; k < currentNeuron->getSynapsesNum(); k++) {
    //                 // Update the weight of every synapse.
    //
    //                 // Calculate the weight delta.
    //                 // dWeight = this->learningRate * currentNeuron->getError() * currentNeuron->getSynapse(k)->getInputNeuron()->getDValue() * currentNeuron->getSynapse(k)->getInputNeuron()->getValue();
    //
    //                 // Calculate the custom weight delta.
    //                 dWeight = this->learningRate * this->errors->getItem(i) * currentNeuron->getSynapse(k)->getInputNeuron()->getValue();
    //
    //                 // Apply the delta weight.
    //                 currentNeuron->getSynapse(k)->setWeight(currentNeuron->getSynapse(k)->getWeight() + dWeight);
    //             }
    //         }
    //     }
    // }
}
