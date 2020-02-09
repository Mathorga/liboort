#ifndef __EXPERIENCE__
#define __EXPERIENCE__

#include "utils.h"

namespace oort {
    class Experience {
    public:
        Experience(dtensor1d inputs, dtensor1d outputs);
        Experience(uint32_t inputsNum, uint32_t outputsNum);
        Experience();

        void print();

        // Getters.
        neuron_value_t getInput(uint32_t index);
        neuron_value_t getOutput(uint32_t index);
        dtensor2d getInputs();
        dtensor2d getOutputs();
        uint32_t getInputsNum();
        uint32_t getOutputsNum();

        // Setters.
        void setInputs(neuron_value_t* inputs, uint32_t inputsNum);
        void setInputs(dtensor1d inputs);
        void setOutputs(neuron_value_t* outputs, uint32_t outputsNum);
        void setOutputs(dtensor1d outputs);

    private:
        dtensor1d inputs;
        dtensor1d outputs;
    };
}

#endif
