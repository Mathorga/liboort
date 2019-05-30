#include "Neuron.h"

neurons_num_t Neuron::getId() {
    return this->id;
}

Neuron::NeuronType Neuron::getType() {
    return this->type;
}

neuron_value_t Neuron::getValue() {
    return this->value;
}

void Neuron::setValue(neuron_value_t value) {
    this->value = value;
}

void Neuron::setType(NeuronType type) {
    this->type = type;
}
