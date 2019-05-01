#include "Neuron.h"

neuron_value_t Neuron::getValue() {
    return this->value;
}

Neuron::NeuronType Neuron::getType() {
    return this->type;
}

void Neuron::setValue(neuron_value_t value) {
    this->value = value;
}

void Neuron::setType(NeuronType type) {
    this->type = type;
}
