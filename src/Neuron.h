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

namespace Oort {
    class Neuron {
    public:
        // Definition of the neuron types.
        enum NeuronType {
            typeInput = 0,
            typeOutput = 1,
            typeHidden = 2
        };

        // Getters.
        // Returns the type of the neuron, meaning typeInput, typeOutput or typeHidden.
        NeuronType getType();
        // Returns the value of the neuron.
        // Typically the neuron's value needs to be calculated before it's returned.
        neuron_value_t getValue();

        // Setters.
        // Sets the type of the neuron.
        void setType(NeuronType type);
        // Sets the value of the neuron.
        void setValue(neuron_value_t value);

    protected:
        // Type of the neuron.
        NeuronType type;
        // Value of the neuron.
        neuron_value_t value;
    };
}

#endif
