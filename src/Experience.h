#ifndef __EXPERIENCE__
#define __EXPERIENCE__

#include "utils.h"

namespace oort {
    class Experience {
    public:
        Experience(tensor::dtensor1d inputs, tensor::dtensor1d outputs);
        Experience(uint32_t inputsNum, uint32_t outputsNum);
        Experience();

        void print();

        // Getters.
        double getInput(uint32_t index);
        double getOutput(uint32_t index);
        tensor::dtensor1d getInputs();
        tensor::dtensor1d getOutputs();
        uint32_t getInputsNum();
        uint32_t getOutputsNum();

        // Setters.
        void setInputs(double* inputs, uint32_t inputsNum);
        void setInputs(tensor::dtensor1d inputs);
        void setOutputs(double* outputs, uint32_t outputsNum);
        void setOutputs(tensor::dtensor1d outputs);

    private:
        tensor::dtensor1d inputs;
        tensor::dtensor1d outputs;
    };
}

#endif
