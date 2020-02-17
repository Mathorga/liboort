#include "Model.h"
#include "GradientDescender.h"
#include "Knowledge.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    uint32_t layerSizes[3] = {2, 4, 1};

    Model* testGraph = new Model(3, layerSizes);
    Trainer* optim = new GradientDescender();

    math::dtensor1d inputs;
    math::alloc(&inputs, 2);
    inputs.values[0] = 0.0;
    inputs.values[1] = 1.0;

    double sTime = 0.0;
    double eTime = 0.0;

    testGraph->feed(inputs);
    testGraph->compute();

    math::dtensor1d outs = testGraph->getOutput();

    printf("\nOUTPUT %f\n", outs.values[0]);

    return 0;
}
