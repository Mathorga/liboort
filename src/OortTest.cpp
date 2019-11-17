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
    // uint16_t outputNum = 1;
    // char* modelFileName = nullptr;
    // // float* expectedOutput;
    // neuron_value_t* newExpectedOut;



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
    // ############################################### NERVE TESTING ##################################################

    KnowledgeParser* kp = new KnowledgeParser();
    kp->readFile((char*) "./res/knl/Oort2.knl");

    LayeredPerceptronModelParser* lpmp = new LayeredPerceptronModelParser();
    // lpmp->readFile((char*) "./res/mdl/testLPM.mdl");
    // lpmp->getModel()->print();
    // lpmp->writeFile((char*) "./res/mdl/NEWtestLPM.mdl");


    Vector<vector_size_t>* layerSizes = new Vector<vector_size_t>();
    // Add input layer.
    layerSizes->addLast(200);

    // Add hidden layer.
    layerSizes->addLast(5);

    // Add hidden layer.
    layerSizes->addLast(5);

    // Add hidden layer.
    layerSizes->addLast(5);

    // Add output layer.
    layerSizes->addLast(3);

    // Create the network.
    // LayeredPerceptronNetwork* nnn = new LayeredPerceptronNetwork(new LayeredPerceptronModel(layerSizes));
    // lpmp->setModel(nnn->getModel());
    // lpmp->readFile((char*) "./res/mdl/NEWtestLPM.mdl");
    LayeredPerceptronNetwork* nnn = new LayeredPerceptronNetwork(new LayeredPerceptronModel(layerSizes));

    double startTime = getTime();
    printf("\noutput: %f %f %f\n", nnn->getOutput()[0], nnn->getOutput()[1], nnn->getOutput()[2]);
    for (uint i = 0; i < 1; i++) {
        nnn->setInput(kp->getKnowledge()->getExperiencesVector()->getLast()->getInputs());
        nnn->setExpectedOutput(kp->getKnowledge()->getExperiencesVector()->getLast()->getOutputs());
        nnn->run();
        nnn->print();
        nnn->correct();
    }
    nnn->setInput(kp->getKnowledge()->getExperiencesVector()->getLast()->getInputs());
    nnn->run();
    nnn->print();
    printf("\noutput: %f %f %f\n", nnn->getOutput()[0], nnn->getOutput()[1], nnn->getOutput()[2]);
    printf("\nexpected: %f %f %f\n", kp->getKnowledge()->getExperiencesVector()->getLast()->getOutputs()[0], kp->getKnowledge()->getExperiencesVector()->getLast()->getOutputs()[1], kp->getKnowledge()->getExperiencesVector()->getLast()->getOutputs()[2]);
    printf("\ninputsNum %d outputsNum %d\n", kp->getKnowledge()->getInputsNum(), kp->getKnowledge()->getOutputsNum());
    // nnn->train(kp->getKnowledge(), 10);
    // lpmp->writeFile((char*) "./res/mdl/NEWtestLPM.mdl");
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
        // printf("\noutput: %f %f %f\n", nnn->getOutput()[0], nnn->getOutput()[1], nnn->getOutput()[2]);
    }



    // Vector<vector_size_t>* layerSizes = new Vector<vector_size_t>();
    // // Add input layer.
    // layerSizes->addLast(1);
    // layerSizes->addLast(200);
    //
    // // Add output layer.
    // layerSizes->addLast(1);
    //
    // LayeredPerceptronNetwork* lpn = new LayeredPerceptronNetwork(new LayeredPerceptronModel(layerSizes));
    //
    // lpn->print();
    //
    // neuron_value_t input = 0.4;
    // neuron_value_t expectedOutput = 0.8;
    //
    // for (uint i = 0; i < 1000000; i++) {
    //     lpn->setInput(&input);
    //     lpn->setExpectedOutput(&expectedOutput);
    //     lpn->run();
    //     // lpn->print();
    //     // usleep(1000);
    //     lpn->correct();
    // }
    // lpn->run();
    // lpn->print();






    return 0;
}
