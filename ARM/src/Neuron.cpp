#include "Neuron.h"

NEURON_VALUE_T Neuron::getValue() {
    return this->value;
}

void Neuron::setValue(NEURON_VALUE_T value) {
    this->value = value;
}
