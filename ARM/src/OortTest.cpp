#include "Nerve.h"
#include "SimpleBrain.h"
#include "SimpleModelParser.h"
#include "SparsePerceptronNetwork.h"
#include "SparsePerceptronModelParser.h"
#include "utils.h"

int main(int argc, char const *argv[]) {
    uint16_t inputNum = 1;
    uint16_t outputNum = 1;
    char* modelFileName = NULL;
    float* expectedOutput;
    neuron_value_t* newExpectedOut;

    double startTime = 0;
    double endTime = 0;
    double execTime = 0;

    // Input check.
    if (argc > 2 || argc <= 1) {
        printf("Usage: %s [modelFile]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        modelFileName = (char*) argv[1];
    }

    SparsePerceptronModelParser* spmParser = new SparsePerceptronModelParser();
    spmParser->readFile(modelFileName);
    SparsePerceptronNetwork* brain = new SparsePerceptronNetwork(spmParser->getModel());
    // SparsePerceptronNetwork* brain = new SparsePerceptronNetwork(400, 2);
    // spmParser->setModel(brain->getModel());
    // spmParser->writeFile(modelFileName);

    newExpectedOut = (neuron_value_t*) malloc(outputNum * sizeof(neurons_num_t));
    newExpectedOut[0] = 0.6;
    brain->setExpectedOutput(newExpectedOut);
    brain->print();

    // Main loop of the program.
    for (uint16_t i = 0;; i ++) {
        startTime = getTime();
        brain->run();
        brain->correct();
        // brain->describe();
        // brain->run();
        endTime = getTime();
        execTime = endTime - startTime;
        usleep(10000);
        // printf("Time: %f s\n", execTime);
        printf("Output: %.7f\n", brain->getOutput()[0]);
    }

    return 0;
}
