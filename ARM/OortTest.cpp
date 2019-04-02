#include "Nerve.h"
#include "SimpleBrain.h"
#include "ModelParser.h"
#include "utils.h"

int main(int argc, char const *argv[]) {
    uint16_t inputNum = 1;
    uint16_t outputNum = 1;
    char* modelFileName = NULL;
    float* expectedOutput;

    double startTime = 0;
    double endTime = 0;
    double execTime = 0;

    float* output;

    // Input check.
    if (argc > 2 || argc <= 1) {
        printf("Usage: %s [modelFile]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        modelFileName = (char*) argv[1];
    }

    // Get Model from file and create a Brain from it.
    ModelParser* parser = new ModelParser();
    parser->readFile(modelFileName);
    SimpleBrain* brain = new SimpleBrain(parser->getModel());

    // SimpleBrain* testBrain = new SimpleBrain(8000, 1);
    // ModelParser* testParser = new ModelParser();
    // testParser->setModel(testBrain->getModel());
    // testParser->writeFile("./res/mdl/8000in1out.xml");

    brain->run();
    // brain->describe();

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



    uint8_t a = 37;
    uint8_t b = 201;
    uint8_t c = (a * b) / 255;
    printf("\n%d * %d = %d\n", a, b, c);




    srand(time(NULL));
    uint8_t* image = (uint8_t*) malloc(400 * sizeof(uint8_t));
    for (uint16_t i = 0; i < 400; i++) {
        image[i] = iRandBetween(0, 255);
    }
    dump(image, 20, "./res/dump.ppm");


    dump(readImage("/home/luka/Pictures/IMG-20181105-WA0072.ppm", 20), 20, "./res/dump2.ppm");



    expectedOutput = (float*) malloc(outputNum * sizeof(float));
    expectedOutput[0] = 0.6;
    brain->setExpectedOutput(expectedOutput);
    printf("\n\nExpected output: %f\n\n", expectedOutput[0]);

    // Main loop of the program.
    float op;
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
