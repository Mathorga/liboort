/*
********************************************************************************
Neuron.h

This file defines the interface for a generic neuron, including default types
and methods to manage it.
Copyright (C) 2019  Luka Micheletti

********************************************************************************
*/

#ifndef __NEURON__
#define __NEURON__

#include "utils.h"

// Definition of the neuron value type.
#define neuron_value_t float

class Neuron {
public:
    // Definition of the neuron types.
    enum NeuronType {
        typeInput = 0,
        typeOutput = 1,
        typeHidden = 2
    };

    // Getters.
    NeuronType getType();
    neuron_value_t getValue();

    // Setters.
    void setType(NeuronType type);
    void setValue(neuron_value_t value);

protected:
    NeuronType type;
    // Value of the neuron.
    neuron_value_t value;
};

#endif
