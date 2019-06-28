#ifndef __PERCEPTRON_SYNAPSE__
#define __PERCEPTRON_SYNAPSE__

#include "Synapse.h"
#include "Perceptron.h"

class Perceptron;

class PerceptronSynapse : public Synapse {
public:
    static const synapse_weight_t DEFAULT_WEIGHT;

    // Constructors.
    PerceptronSynapse();
    PerceptronSynapse(synapse_weight_t weight);
    PerceptronSynapse(Perceptron* inputNeuron);
    PerceptronSynapse(Perceptron* inputNeuron, synapse_weight_t weight);

    void print();

    // Getters.
    Perceptron* getInputNeuron();
    neurons_num_t getInputId();

private:
    Perceptron* inputNeuron;
};

#endif
