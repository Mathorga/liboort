#include "Nerve.h"
#include "SimpleBrain.h"
#include "ModelParser.h"
#include "utils.h"

int main(int argc, char const *argv[]) {
    uint16_t inputNum = 1;
    uint16_t outputNum = 1;
    char *modelFileName = (char *) "./res/modelTest.xml";
    double *expectedOutput;

    double startTime = 0;
    double endTime = 0;
    double execTime = 0;

    double *output;

    // Input check.
    if (argc > 3) {
        printf("Usage: %s [inputNum] [outputNum]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        inputNum = atoi(argv[1]);
    }
    if (argc > 2) {
        outputNum = atoi(argv[2]);
    }

    SimpleBrain *brain = new SimpleBrain(inputNum, outputNum);
    ModelParser *parser = new ModelParser();

    parser->readFile(modelFileName);
    printf("\nParsed File\n");

    brain->describe();
    brain->run();

    brain->addNeuron(0, brain->getNeuronsNum() - 1);
    brain->run();
    // brain->describe();

    brain->addNeuron(0, brain->getNeuronsNum() - 1);
    brain->run();
    // brain->describe();

    brain->addSynapse(3, brain->getNeuronsNum() - 1);
    brain->run();
    // brain->describe();

    expectedOutput = (double *) malloc(outputNum * sizeof(double));
    expectedOutput[0] = 0.5;
    brain->setExpectedOutput(expectedOutput);
    printf("\n\n%f\n\n", expectedOutput[0]);

    free(brain);

    brain = new SimpleBrain(parser->getModel());
    brain->describe();
    parser->setModel(brain->getModel());
    parser->writeFile("./res/output.xml");

    free(brain);

    parser->readFile("./res/output.xml");
    brain = new SimpleBrain(parser->getModel());
    brain->describe();

    // Main loop of the program.
    for (uint16_t i = 0;; i ++) {
        startTime = getTime();
        brain->run();
        brain->correct();
        // brain->run();
        endTime = getTime();
        execTime = endTime - startTime;
        // usleep(10000);
        // printf("Time: %f s\n", execTime);
        // printf("Output: %f\n", brain->getOutput()[0]);
    }

    return 0;
}
