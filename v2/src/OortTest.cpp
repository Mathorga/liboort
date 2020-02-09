#include "Model.h"
#include "GDTrainer.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    array_size_t layerSizes[3] = {2, 4, 1};

    Model* testGraph = new Model(3, layerSizes);
    Trainer* optim = new GDTrainer();

    math::dtensor1d inputs;
    math::alloc(&inputs, 2);
    inputs.values[0] = 0.0;
    inputs.values[1] = 1.0;

    double sTime = 0.0;
    double eTime = 0.0;

    testGraph->feed(inputs);
    testGraph->compute();

    double* outs = testGraph->getOutput();

    printf("\nOUTPUT %f\n", outs[0]);

    printf("\n%d\n", -2 % 3);


    return 0;
}
