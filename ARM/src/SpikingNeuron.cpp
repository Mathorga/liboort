#include "SpikingNeuron.h"

SpikingNeuron::SpikingNeuron() {
    this->value = 0;
}

SpikingNeuron::SpikingNeuron(NEURON_VALUE_T value) {
    this->value = value;
}
