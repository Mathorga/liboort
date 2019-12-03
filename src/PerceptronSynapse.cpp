#include "PerceptronSynapse.h"

namespace Oort {
    const synapse_weight_t PerceptronSynapse::DEFAULT_WEIGHT = 0.2;
    // const synapse_weight_t PerceptronSynapse::DEFAULT_WEIGHT = rand() / RAND_MAX;

    PerceptronSynapse::PerceptronSynapse(Perceptron* inputNeuron, synapse_weight_t weight) {
        this->weight = weight;
        this->inputNeuron = inputNeuron;
    }

    PerceptronSynapse::PerceptronSynapse(Perceptron* inputNeuron) : PerceptronSynapse(inputNeuron, DEFAULT_WEIGHT) {}

    PerceptronSynapse::PerceptronSynapse(synapse_weight_t weight) : PerceptronSynapse(nullptr, weight) {}

    PerceptronSynapse::PerceptronSynapse() : PerceptronSynapse(nullptr, DEFAULT_WEIGHT) {}

    void PerceptronSynapse::print() {
        setPrintColor(ANSI_COLOR_YELLOW);
        printf("\t\t|SYNAPSE\n");
        printf("\t\t|Input %d\n", this->inputNeuron->getId());
        printf("\t\t|Weight %.9f\n", this->weight);
        printf("\t\t|DWeight %.9f\n", this->dWeight);
        // printf("\t\t|DeltaWeight %.9f\n", this->deltaWeight);
        setPrintColor(ANSI_COLOR_RESET);
    }

    Perceptron* PerceptronSynapse::getInputNeuron() {
        return this->inputNeuron;
    }

    vector_size_t PerceptronSynapse::getInputId() {
        return this->inputNeuron->getId();
    }

    synapse_weight_t PerceptronSynapse::getDWeight() {
        return this->dWeight;
    }

    void PerceptronSynapse::setDWeight(synapse_weight_t dWeight) {
        this->dWeight = dWeight;
    }

    void PerceptronSynapse::setDeltaWeight(synapse_weight_t deltaWeight) {
        this->deltaWeight = deltaWeight;
    }
}
