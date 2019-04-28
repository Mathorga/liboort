#include "Neuron.h"

neuron_value_t Neuron::getValue() {
    return this->value;
}

void Neuron::setValue(neuron_value_t value) {
    this->value = value;
}
