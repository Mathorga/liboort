#include "ModelParser.h"

namespace Oort {
    const uint8_t ModelParser::TOTAL_NEURONS_NUM_DEPTH = 4;
    const uint8_t ModelParser::INPUT_NEURONS_NUM_DEPTH = 4;
    const uint8_t ModelParser::OUTPUT_NEURONS_NUM_DEPTH = 4;
    const uint8_t ModelParser::NEURON_ID_DEPTH_DEPTH = 1;
    const uint8_t ModelParser::NEURON_TYPE_DEPTH_DEPTH = 1;
    const uint8_t ModelParser::NEURON_SYNAPSES_NUM_DEPTH_DEPTH = 1;
    const uint8_t ModelParser::SYNAPSE_WEIGHT_DEPTH_DEPTH = 1;

    ModelParser::ModelParser() {
        // Set default depths.
        this->neuronIdDepth = 1;
        this->neuronTypeDepth = 1;
        this->neuronSynapsesNumDepth = 1;
        this->synapseWeightDepth = 1;
    }

    void ModelParser::setNeuronIdDepth(uint8_t neuronIdDepth) {
        this->neuronIdDepth = neuronIdDepth;
    }

    void ModelParser::setNeuronTypeDepth(uint8_t neuronTypeDepth) {
        this->neuronTypeDepth = neuronTypeDepth;
    }
}
