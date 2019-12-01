/*
********************************************************************************
Perceptron.h

This file defines the interface for the perceptron neuron. by default the neuron
is sigmoid activated.

Copyright (C) 2019  Luka Micheletti
********************************************************************************
*/

#ifndef __PERCEPTRON__
#define __PERCEPTRON__

#include "Neuron.h"
#include "Vector.h"
#include "PerceptronSynapse.h"

#define perceptron_error_t double
#define perceptron_input_t double

namespace Oort {
    class PerceptronSynapse;
    class Perceptron : public Neuron {
    public:
        static const neuron_value_t DEFAULT_VALUE;
        static const perceptron_error_t DEFAULT_ERROR;
        static Perceptron getNullPerceptron();

        // Constructors.
        Perceptron(vector_size_t id);
        Perceptron(vector_size_t id, Neuron::NeuronType type);
        Perceptron(vector_size_t id, neuron_value_t value);
        Perceptron(vector_size_t id, neuron_value_t value, Neuron::NeuronType type);
        Perceptron(vector_size_t id, neuron_value_t value, vector_size_t synapsesNum);
        Perceptron(Perceptron& other);

        void print();

        // Getters.
        vector_size_t getId();
        neuron_value_t getDValue();
        // neuron_value_t getDInput();
        // neuron_value_t getDOutput();
        perceptron_error_t getError();
        neuron_value_t getGradient();
        neuron_value_t getExpectedOutput();
        vector_size_t getSynapsesNum();
        Vector<PerceptronSynapse>* getSynapses();
        PerceptronSynapse* getSynapse(vector_size_t index);
        Perceptron** getInputs();

        // Setters.
        void setDValue(neuron_value_t dValue);
        // void setDInput(neuron_value_t dInput);
        // void setDOutput(neuron_value_t dOutput);
        void setError(perceptron_error_t error);
        void addError(perceptron_error_t error);
        void setGradient(neuron_value_t gradient);
        void setExpectedOutput(neuron_value_t expectedOutput);

    private:
        vector_size_t id;
        neuron_value_t dValue;
        // neuron_value_t dInput;
        // neuron_value_t dOutput;
        perceptron_error_t error;
        neuron_value_t gradient;
        neuron_value_t expectedOutput;
        // perceptron_error_t delta;
        // perceptron_error_t partialDelta;

        Vector<PerceptronSynapse>* synapses;
    };
}

#endif
