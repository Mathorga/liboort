/*
********************************************************************************
ModelParser.h

Model files' (.mdl) specification defines a header made of 16 bytes,
representing respectively: the total number of neurons of the model (4B), the
number of input neurons (4B), the number of output neurons (4B), the depth used
to report each neuron's id (1B), the depth used to store each neuron's type
(1B), the depth for each neuron's synapses number (1B) and the depth for each
synapse's weight (1B).
The header is followed by the informations on neurons and synapses themselves.
Each neuron is defined by three values: neuron id, neuron type and synapses
number.
After each neuron, all its synapses are listed.
Each synapse is defined by two values: input neuron id and synapse weight.
Model files use big-endian encoding for values.

This file defines a parser (reader and writer) of a Model object.
Assign a Model object using setModel() before writing it to a file.
Use getModel() after reading a file to get the parsed Model object.

Copyright (C) 2019  Luka Micheletti
********************************************************************************
*/

#ifndef __MODEL_PARSER__
#define __MODEL_PARSER__

#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "../lib/rapidxml-1.13/rapidxml_utils.hpp"
#include "../lib/rapidxml-1.13/rapidxml_print.hpp"
#include "Parser.h"

namespace Oort {
    class ModelParser : public Parser {
    public:
        // Constructor.
        ModelParser();

        // Setters.
        void setNeuronIdDepth(uint8_t neuronIdDepth);
        void setNeuronTypeDepth(uint8_t neuronTypeDepth);
    protected:
        static const uint8_t TOTAL_NEURONS_NUM_DEPTH;
        static const uint8_t INPUT_NEURONS_NUM_DEPTH;
        static const uint8_t OUTPUT_NEURONS_NUM_DEPTH;
        static const uint8_t NEURON_ID_DEPTH_DEPTH;
        static const uint8_t NEURON_TYPE_DEPTH_DEPTH;
        static const uint8_t NEURON_SYNAPSES_NUM_DEPTH_DEPTH;
        static const uint8_t SYNAPSE_WEIGHT_DEPTH_DEPTH;
        uint32_t neuronIdDepth;
        uint32_t neuronTypeDepth;
        uint32_t neuronSynapsesNumDepth;
        uint32_t synapseWeightDepth;
    };
}

#endif
