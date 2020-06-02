#ifndef __EXPERIENCE__
#define __EXPERIENCE__

#include "utils.h"

namespace oort {
    class Experience {
    public:
        Experience(math::dtensor1d inputs, math::dtensor1d outputs);
        Experience(uint32_t inputsNum, uint32_t outputsNum);
        Experience();

        void print();

        // Getters.
        double getInput(uint32_t index);
        double getOutput(uint32_t index);
        math::dtensor1d getInputs();
        math::dtensor1d getOutputs();
        uint32_t getInputsNum();
        uint32_t getOutputsNum();

        // Setters.
        void setInputs(double* inputs, uint32_t inputsNum);
        void setInputs(math::dtensor1d inputs);
        void setOutputs(double* outputs, uint32_t outputsNum);
        void setOutputs(math::dtensor1d outputs);

    private:
        math::dtensor1d inputs;
        math::dtensor1d outputs;
    };
}

#endif
