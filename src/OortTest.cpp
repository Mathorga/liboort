#include "Nerve.h"
#include "SparsePerceptronNetwork.h"
#include "SparsePerceptronModelParser.h"
#include "LayeredPerceptronNetwork.h"
#include "LayeredPerceptronModelParser.h"
#include "KnowledgeParser.h"
#include "SerialNerve.h"

using namespace Oort;

int main(int argc, char const *argv[]) {
    // uint16_t inputNum = 1;
    uint16_t outputNum = 1;
    char* modelFileName = nullptr;
    // float* expectedOutput;
    neuron_value_t* newExpectedOut;

    // double startTime = 0;
    // double endTime = 0;
    // double execTime = 0;

    // Input check.
    if (argc > 2 || argc <= 1) {
        printf("Usage: %s [modelFile]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        modelFileName = (char*) argv[1];
    }

    SparsePerceptronModelParser* parser = new SparsePerceptronModelParser();
    parser->readFile(modelFileName);
    SparsePerceptronNetwork* brain = new SparsePerceptronNetwork(parser->getModel());

    // LayeredPerceptronModel* layeredModel = new LayeredPerceptronModel();
    // layeredModel->print();
    // SparsePerceptronNetwork* brain = new SparsePerceptronNetwork(5184, 3);
    // parser->setModel(brain->getModel());
    // parser->writeFile(modelFileName);


    // Set expected output for the current input.
    newExpectedOut = (neuron_value_t*) malloc(outputNum * sizeof(vector_size_t));
    newExpectedOut[0] = 0.6;
    brain->setExpectedOutput(newExpectedOut);
    // brain->print();










    // KnowledgeParser* kp = new KnowledgeParser();
    // kp->readFile((char*) "./res/knl/testBinTrue.knl");
    // kp->getKnowledge()->print();
    // KnowledgeParser* kp2 = new KnowledgeParser();
    // kp2->setKnowledge(kp->getKnowledge());
    // kp2->setDepth(2);
    // kp2->writeFile((char*) "./res/knl/test2.knl");
    //
    // SparsePerceptronModelParser* par = new SparsePerceptronModelParser();
    // par->setModel(new SparsePerceptronModel(1296, 3, true));
    // par->writeFile((char*) "./res/mdl/1296in3out.mdl");


    KnowledgeParser* kp = new KnowledgeParser();
    kp->readFile((char*) "./res/knl/Oort2.knl");
    // kp->getKnowledge()->print();
    SparsePerceptronModelParser* par = new SparsePerceptronModelParser();
    par->readFile((char*) "./res/mdl/trained.mdl");

    // Testing training on example knowledge.
    SparsePerceptronNetwork* testNet = new SparsePerceptronNetwork(par->getModel());
    testNet->setInput(kp->getKnowledge()->getExperience(0)->getInputs());
    // testNet->setInput(kp->getKnowledge()->getExperience(0)->getInputs());
    // testNet->print();
    testNet->run();
    printf("\nOutput %f %f %f\n", testNet->getOutput()[0], testNet->getOutput()[1], testNet->getOutput()[2]);






    // FILE* file = fopen("/dev/ttyUSB0", "w");
    // int32_t x = 0;
    // for (uint32_t i = 0; i < 100; i++) {
    //     fprintf(file, "%d", i + 10); //Writing to the file
    //     usleep(1000);
    //     fscanf(file, "%d", &x);
    //     printf("\n%d\n", x);
    // }
    // fclose(file);







    // ############################################### NERVE TESTING ##################################################
    /*byte* data = (byte*) malloc(3);
    data[0] = 100;
    data[1] = 101;
    data[2] = 102;
    Nerve* nerve = new SerialNerve((char*) "/dev/ttyUSB0");
    byte newData[256];

    for (uint16_t i = 0; i < 100; i++) {
        // Set data to send.
        for (uint8_t j = 0; j < 3; j++) {
            data[j] = i + j;
        }

        // Send data.
        nerve->send(data, 3);
        // Receive data.
        nerve->receive(newData, 3);

        // Show received data.
        for (uint8_t j = 0; j < 3; j++) {
            printf("%d ", newData[j]);
        }
        printf("\n");
    }

    delete nerve;
    // nerve->closeStream();*/



    LayeredPerceptronModelParser* lpmp = new LayeredPerceptronModelParser();
    lpmp->readFile((char*) "./res/mdl/testLPM.mdl");
    lpmp->getModel()->print();


    Vector<vector_size_t>* layerSizes = new Vector<vector_size_t>();
    // Add input layer.
    layerSizes->addLast(1296);

    // Add hidden layer.
    layerSizes->addLast(5);

    // Add hidden layer.
    layerSizes->addLast(5);

    // Add hidden layer.
    layerSizes->addLast(5);

    // Add output layer.
    layerSizes->addLast(3);

    // Create the network.
    LayeredPerceptronNetwork* nnn = new LayeredPerceptronNetwork(new LayeredPerceptronModel(layerSizes));

    printf("\nKnowledge size %d\n", kp->getKnowledge()->getExperience(0)->getInputsNum());

    double startTime = getTime();
    nnn->train(kp->getKnowledge(), 10);
    double endTime = getTime();

    printf("\nTraining completed\nTotal training time %fs\n", endTime - startTime);

    // nnn->print();
    nnn->run();
    // nnn->print();
    for (int i = 0;; i++) {
        // if (i % 100 == 0) {
        //     nnn->print();
        // }
        nnn->run();
    }








    return 0;
}
