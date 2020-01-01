#ifndef __NEURAL_GRAPH__
#define __NEURAL_GRAPH__

#define neuron_value_t double
#define synapse_weight_t double

namespace Oort {

    class NeuralGraph {
    private:
        neuron_value_t** neuronInputs;
        neuron_value_t** neuronOutputs;
        synapse_weight_t** synapses;
        uint8_t** synapsesActivations;
    };
}

#endif
