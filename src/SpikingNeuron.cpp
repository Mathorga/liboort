#include "SpikingNeuron.h"

SpikingNeuron::SpikingNeuron() {
    this->value = 0;
}

SpikingNeuron::SpikingNeuron(neuron_value_t value) {
    this->value = value;
}
