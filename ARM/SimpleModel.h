#ifndef __SIMPLE_MODEL__
#define __SIMPLE_MODEL__

#include "utils.h"

class SimpleModel : public Model {
public:
    // Definition of the neuron data type.
    typedef struct {
        NeuronType type;
        uint16_t value;
        bool enabled;
    } _Neuron;

    // Definition of the synapse data type.
    typedef struct {
        uint16_t inputNeuron;
        uint16_t outputNeuron;
        bool state;
        bool nextState;
        bool enabled;
    } _Synapse;

    void describe();
    void randomizeSynapsesWeights();

    uint16_t getInputNum();
    uint16_t getOutputNum();
    uint16_t getHiddenNum();
    uint16_t getNeuronsNum();
    uint16_t getSynapsesNum();
    _Neuron* getNeurons();
    _Synapse* getSynapses();

    void setInputNum(uint16_t num);
    void setOutputNum(uint16_t num);
    void setHiddenNum(uint16_t num);
    void setNeuronsNum(uint16_t num);
    void setSynapsesNum(uint16_t num);
    void setNeurons(_Neuron *inputNeurons);
    void setSynapses(_Synapse *inputSynapses);
};

#endif
