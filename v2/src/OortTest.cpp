#include "Model.h"
#include "GradientDescender.h"
#include "Knowledge.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    uint32_t layerSizes[3] = {2, 2, 1};

    Model* testGraph = new Model(3, layerSizes);
    GradientDescender* optim = new GradientDescender();
    optim->setEpochsNum(100);
    optim->setLearningRate(0.1);
    optim->setModel(testGraph);
    optim->setCostFunction(new math::MSE());

    math::dtensor1d ins1;
    math::alloc(&ins1, 2);
    math::dtensor1d outs1;
    math::alloc(&outs1, 1);
    ins1.values[0] = 0.0;
    ins1.values[1] = 0.0;
    outs1.values[0] = 0.0;
    math::dtensor1d ins2;
    math::alloc(&ins2, 2);
    math::dtensor1d outs2;
    math::alloc(&outs2, 1);
    ins2.values[0] = 0.0;
    ins2.values[1] = 1.0;
    outs2.values[0] = 1.0;
    math::dtensor1d ins3;
    math::alloc(&ins3, 2);
    math::dtensor1d outs3;
    math::alloc(&outs3, 1);
    ins3.values[0] = 1.0;
    ins3.values[1] = 0.0;
    outs3.values[0] = 1.0;
    math::dtensor1d ins4;
    math::alloc(&ins4, 2);
    math::dtensor1d outs4;
    math::alloc(&outs4, 1);
    ins4.values[0] = 1.0;
    ins4.values[1] = 1.0;
    outs4.values[0] = 0.0;
    Knowledge ds(2, 1);
    ds.addExperience(Experience(ins4, outs4));
    ds.addExperience(Experience(ins1, outs1));
    ds.addExperience(Experience(ins2, outs2));
    ds.addExperience(Experience(ins3, outs3));

    // testGraph->feed(ds.getExperience(0).getInputs());
    // testGraph->compute();
    // math::dtensor1d out = testGraph->getOutput();
    // printf("\nOUTPUT %f\n", out.values[0]);

    optim->setKnowledge(ds);
    optim->run();


    testGraph->feed(ds.getExperience(2).getInputs());
    testGraph->compute();
    math::dtensor1d out = testGraph->getOutput();
    print(out);

    return 0;
}
