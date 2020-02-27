#include "Model.h"
#include "GradientDescender.h"
#include "Knowledge.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    uint32_t layerSizes[3] = {2, 2, 1};

    Model* testGraph = new Model(3, layerSizes);
    GradientDescender* optim = new GradientDescender();
    optim->setEpochsNum(10000);
    optim->setLearningRate(0.1);

    math::dtensor1d ins;
    math::alloc(&ins, 2);

    double sTime = 0.0;
    double eTime = 0.0;

    testGraph->feed(ins);
    testGraph->compute();

    math::dtensor1d outs = testGraph->getOutput();

    printf("\nOUTPUT %f\n", outs.values[0]);

    return 0;
}
