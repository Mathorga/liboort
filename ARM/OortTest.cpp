#include "Nerve.h"
#include "SimpleBrain.h"
#include "ModelParser.h"
#include "utils.h"

int main(int argc, char const *argv[]) {
    uint16_t inputNum = 1;
    uint16_t outputNum = 1;
    char* modelFileName = NULL;
    double* expectedOutput;

    double startTime = 0;
    double endTime = 0;
    double execTime = 0;

    double* output;

    // Input check.
    if (argc > 2) {
        printf("Usage: %s [modelFile]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        modelFileName = (char *) argv[1];
    }

    // Get Model from file and create a Brain from it.
    // ModelParser* parser = new ModelParser();
    // parser->readFile(modelFileName);
    // SimpleBrain* brain = new SimpleBrain(parser->getModel());

    SimpleBrain* brain = new SimpleBrain(1000, 1);

    // brain->describe();
    brain->run();

    // brain->addNeuron(0, brain->getNeuronsNum() - 1);
    // brain->run();
    // brain->describe();
    //
    // brain->addNeuron(0, brain->getNeuronsNum() - 1);
    // brain->run();
    // brain->describe();
    //
    // brain->addSynapse(3, brain->getNeuronsNum() - 1);
    // brain->run();
    // brain->describe();

    expectedOutput = (double*) malloc(outputNum * sizeof(double));
    expectedOutput[0] = 0.5;
    brain->setExpectedOutput(expectedOutput);
    printf("\n\nExpected output: %f\n\n", expectedOutput[0]);

    // Main loop of the program.
    double op;
    for (uint16_t i = 0;; i ++) {
        startTime = getTime();
        brain->run();
        brain->correct();
        // brain->run();
        endTime = getTime();
        execTime = endTime - startTime;
        usleep(100000);
        printf("Time: %f s\n", execTime);
        // printf("\nnow: %f\tbefore: %f\n", std::abs(0.5f - brain->getOutput()[0]), std::abs(0.5f - op));
        if (std::abs(0.5f - brain->getOutput()[0]) > std::abs(0.5f - op)) {
            // brain->describe();
        }
        op = brain->getOutput()[0];
        printf("Output: %f\n", brain->getOutput()[0]);
    }

    return 0;
}
