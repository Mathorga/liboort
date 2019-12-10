#include "LayeredPerceptronNetwork.h"

namespace Oort {
    const perceptron_error_t LayeredPerceptronNetwork::UNSET_ERROR = -1.0;
    const learning_rate_t LayeredPerceptronNetwork::DEFAULT_LEARNING_RATE = 0.15;
    // const momentum_t LayeredPerceptronNetwork::DEFAULT_MOMENTUM = 0.1;

    LayeredPerceptronNetwork::LayeredPerceptronNetwork() {
        this->model = nullptr;
        this->error = UNSET_ERROR;
        this->learningRate = DEFAULT_LEARNING_RATE;
        // this->momentum = DEFAULT_MOMENTUM;
    }

    LayeredPerceptronNetwork::LayeredPerceptronNetwork(LayeredPerceptronModel* model) {
        this->model = model;
        this->error = UNSET_ERROR;
        // this->momentum = DEFAULT_MOMENTUM;

        // Calculate the learning rate based on the number of neurons:
        // the greater the number of neurons, the lower the learning rate.
        this->learningRate = 1 / (float) this->model->getNeuronsNum();
        this->learningRate = DEFAULT_LEARNING_RATE;
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

    void LayeredPerceptronNetwork::train(Knowledge* knowledge, uint32_t epochsNum, uint32_t batchSize) {
        printf("\n");
        // Check if knowledge is consistent with model.
        if (this->model->getInputsNum() == knowledge->getInputsNum() && this->model->getOutputsNum() == knowledge->getOutputsNum()) {
            // Run the whole training iterationsNum times.
            for (uint32_t i = 0; i < epochsNum; i++) {
                printPercentage(i, epochsNum);

                // Loop through knowledge experiences.
                for (uint32_t j = 0; j < knowledge->getExperiencesNum(); j++) {
                    // Set model inputs based on experience inputs.
                    this->setInput(knowledge->getExperience(j)->getInputs());

                    // Set expected outputs based on experience outputs.
                    this->setExpectedOutput(knowledge->getExperience(j)->getOutputs());

                    // Run the network in order to get outputs.
                    this->run();
                }
                // Correct weights based on the output.
                this->correct();
            }
        } else {
            // Knowledge size is not consistent with model size.
            printf("\n<LayeredPerceptronNetwork::train()> Error: knowledge size not consistent\n");
            // printf("\n%d %d %d %d\n", this->model->getInputsNum(), knowledge->getInputsNum(), this->model->getOutputsNum(), knowledge->getOutputsNum());
        }
        printf("\n");
    }

    neuron_value_t LayeredPerceptronNetwork::activate(neuron_value_t value) {
        // Sigmoid function.
        return (1 / (1 + (exp(-value))));

        // Fast sigmoid functon.
        // return (value / (1 + abs(value)));

        // Hyperbolic tangent function.
        // return tanh(value);

        // Custom hyperbolic tangent function.
        // return ((tanh(0.3 * value) / 2) + 0.5);
    }

    neuron_value_t LayeredPerceptronNetwork::dActivate(neuron_value_t value) {
        // Sigmoid derivative function.
        return this->activate(value) * (1 - this->activate(value));

        // Fast sigmoid derivative function.
        // return (1 / (exp(1 + abs(value)), 2));

        // Hyperbolic tangent derivative function.
        // return (1 - exp(tanh(value), 2));
        // Approximate hyperbolic tangent derivative function.
        // return 1.0 - value * value;

        // Custom hyperbolic tangent derivative function.
        // return (0.15 * (pow(1 / cosh(0.3 * value), 2)));
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

    perceptron_error_t LayeredPerceptronNetwork::getError() {
        return this->error;
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
                // currentNeuron->setValue(this->activate(value + currentNeuron->getBias()));
                currentNeuron->setValue(this->activate(value));

                // Derivative activation.
                // currentNeuron->setDValue(this->dActivate(value + currentNeuron->getBias()));
                currentNeuron->setDValue(this->dActivate(value));

                // Reset error.
                // currentNeuron->setError(Perceptron::DEFAULT_ERROR);

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
        PerceptronSynapse* currentSynapse = nullptr;
        this->error = 0.0;

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

                    // Calculate global error of the network.
                    this->error += currentNeuron->getDOutput();

                    // Compute neuron error.
                    // currentNeuron->setError(currentNeuron->getExpectedOutput() - currentNeuron->getValue());
                    // printf("\nError %f\n", currentNeuron->getError());
                }

                currentNeuron->setDInput(currentNeuron->getDValue() * currentNeuron->getDOutput());

                // Calculate neuron's gradient.
                // currentNeuron->setGradient(currentNeuron->getError() * currentNeuron->getDValue());
                // printf("\ngrad %f\n", currentNeuron->getGradient());

                // Once the gradient for the current neuron is calculated, loop through all the neurons connected to it
                // and add to their error the weighted sum of the gradient of the current.
                for (vector_size_t k = 0; k < currentNeuron->getSynapsesNum(); k++) {

                    currentSynapse = currentNeuron->getSynapse(k);

                    // Calculate the dWeight of the current synapse.
                    currentSynapse->addDWeight(currentSynapse->getInputNeuron()->getValue() * currentNeuron->getDInput());

                    // Update the synapse's input neuron's dOutput.
                    currentSynapse->getInputNeuron()->addDOutput(currentSynapse->getWeight() * currentNeuron->getDInput());
                    // currentNeuron->getSynapse(k)->getInputNeuron()->addError(currentNeuron->getSynapse(k)->getWeight() * currentNeuron->getError());
                }
            }
        }
    }

    void LayeredPerceptronNetwork::adjustWeights() {
        // Store the current neuron and the current synapse for simplicity.
        Perceptron* currentNeuron = nullptr;
        PerceptronSynapse* currentSynapse = nullptr;

        // Loop through layers of the model.
        for (vector_size_t i = 0; i < this->model->getLayersNum(); i++) {
            // Loop through neurons in each layer.
            for (vector_size_t j = 0; j < this->model->getLayer(i)->getSize(); j++) {
                currentNeuron = this->model->getLayer(i)->getItem(j);
                // Loop through synapses in each neuron.
                for (vector_size_t k = 0; k < this->model->getLayer(i)->getItem(j)->getSynapsesNum(); k++) {
                    currentSynapse = currentNeuron->getSynapse(k);

                    // Calculate delta weight.
                    // currentSynapse->setDWeight(this->learningRate *
                    //                            currentSynapse->getInputNeuron()->getValue() *
                    //                            currentNeuron->getGradient() +
                    //                            this->momentum *
                    //                            currentSynapse->getDWeight());

                    // Update the actual synapse weight.
                    // currentSynapse->setDeltaWeight(this->learningRate * currentSynapse->getDWeight());
                    // printf("\nDWeight %f\n", currentSynapse->getDWeight());
                    currentSynapse->setWeight(currentSynapse->getWeight() - (this->learningRate * (currentSynapse->getDWeight() / 4)));

                    // Reset synapse's dWeight.
                    currentSynapse->setDWeight(0.0);
                    // currentSynapse->setWeight(currentSynapse->getWeight() + currentSynapse->getDWeight());
                    // printf("\n%d - %d dWeight %f\n", currentSynapse->getInputNeuron()->getId(), currentNeuron->getId(), currentSynapse->getDWeight());
                }
            }
        }
    }
}
