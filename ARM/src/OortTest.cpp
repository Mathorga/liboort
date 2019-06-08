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

    // Get Model from file and create a Brain from it.
    // SimpleModelParser* parser = new SimpleModelParser();
    // parser->readFile(modelFileName);
    // SimpleBrain* brain = new SimpleBrain(parser->getModel());

    // SimpleBrain* testBrain = new SimpleBrain(8000, 1);
    // ModelParser* testParser = new ModelParser();
    // testParser->setModel(testBrain->getModel());
    // testParser->writeFile("./res/mdl/8000in1out.xml");

    // brain->run();

    // expectedOutput = (float*) malloc(outputNum * sizeof(float));
    // expectedOutput[0] = 0.6;
    // brain->setExpectedOutput(expectedOutput);
    // printf("\n\nExpected output: %f\n\n", expectedOutput[0]);







    SparsePerceptronModelParser* spmParser = new SparsePerceptronModelParser();
    spmParser->readFile(modelFileName);
    SparsePerceptronNetwork* network = new SparsePerceptronNetwork(spmParser->getModel());
    // SparsePerceptronNetwork* network = new SparsePerceptronNetwork(5, 2);
    // spmParser->setModel(network->getModel());
    // spmParser->writeFile(modelFileName);
    // network->print();

    newExpectedOut = (neuron_value_t*) malloc(outputNum * sizeof(neurons_num_t));
    newExpectedOut[0] = 0.6;
    // SparsePerceptronNetwork* network = new SparsePerceptronNetwork(parser->getModel()->getInputNum(), parser->getModel()->getOutputNum());
    network->setExpectedOutput(newExpectedOut);
    network->print();

    // Main loop of the program.
    for (uint16_t i = 0;; i ++) {
        if (i % 100 == 0) {
            network->print();
        }
        startTime = getTime();
        network->run();
        network->correct();
        // brain->describe();
        // brain->run();
        endTime = getTime();
        execTime = endTime - startTime;
        usleep(10000);
        // printf("Time: %f s\n", execTime);
        printf("Output: %.7f\n", network->getOutput()[0]);
    }

    return 0;
}
