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

    // #################################################################################################################
    Vector<vector_size_t>* layerSizes = new Vector<vector_size_t>();
    layerSizes->addLast(2);
    layerSizes->addLast(4);
    layerSizes->addLast(1);
    LayeredPerceptronModel* model = new LayeredPerceptronModel(layerSizes);
    LayeredPerceptronNetwork* network = new LayeredPerceptronNetwork(model);

    Vector<neuron_value_t>* inputs = new Vector<neuron_value_t>();
    Vector<neuron_value_t>* expectedOutputs = new Vector<neuron_value_t>();
    for (int i = 0; i < 1000000; i++) {
        // perceptron_error_t error = 0.0;
        // inputs->empty();
        // expectedOutputs->empty();
        // double in1 = 0.01;
        // double in2 = 0.01;
        // inputs->addLast(in1);
        // inputs->addLast(in2);
        // expectedOutputs->addLast(0.0184);
        // network->setInput(inputs);
        // network->setExpectedOutput(expectedOutputs);
        // network->run();
        // network->computeError();
        // error += network->getError();
        //
        // inputs->empty();
        // expectedOutputs->empty();
        // inputs->addLast(0.989);
        // inputs->addLast(0.992);
        // expectedOutputs->addLast(0.0112);
        // network->setInput(inputs);
        // network->setExpectedOutput(expectedOutputs);
        // network->run();
        // network->computeError();
        // error += network->getError();
        //
        // inputs->empty();
        // expectedOutputs->empty();
        // inputs->addLast(0.0117);
        // inputs->addLast(0.9992);
        // expectedOutputs->addLast(0.9981);
        // network->setInput(inputs);
        // network->setExpectedOutput(expectedOutputs);
        // network->run();
        // network->computeError();
        // error += network->getError();
        //
        // inputs->empty();
        // expectedOutputs->empty();
        // inputs->addLast(0.9792);
        // inputs->addLast(0.0109);
        // expectedOutputs->addLast(0.9841);
        // network->setInput(inputs);
        // network->setExpectedOutput(expectedOutputs);
        // network->run();
        // network->computeError();
        // error += network->getError();
        //
        // network->adjustWeights(4);
        // printf("\nERROR %f\n", error);
        // // network->print();
        // // printf("\n%d expected %f actual %f\n", i, *(expectedOutputs->getLast()), network->getOutput()[0]);
        // // network->print();
        // // usleep(1000000);




        // network->print();
        perceptron_error_t error = 0.0;
        inputs->empty();
        expectedOutputs->empty();
        double in1 = (double) (rand() % 2);
        double in2 = (double) (rand() % 2);
        // in1 = in1 == 0.0 ? 0.01 : 0.99;
        // in2 = in2 == 0.0 ? 0.01 : 0.99;
        inputs->addLast(in1);
        inputs->addLast(in2);
        expectedOutputs->addLast(in1 == in2 ? 0.0 : 1.0);
        network->setInput(inputs);
        network->setExpectedOutput(expectedOutputs);
        network->run();
        // network->print();
        network->computeError();
        error += network->getError();
        network->adjustWeights(1);
        printf("\nERROR %f\n", error);
    }

    // network->adjustWeights();
    inputs->empty();
    inputs->addLast(0.0);
    inputs->addLast(0.0);
    network->setInput(inputs);
    network->run();
    printf("\nValue %f\n", network->getOutput()[0]);

    inputs->empty();
    inputs->addLast(1.0);
    inputs->addLast(1.0);
    network->setInput(inputs);
    network->run();
    printf("\nValue %f\n", network->getOutput()[0]);

    inputs->empty();
    inputs->addLast(0.0);
    inputs->addLast(1.0);
    network->setInput(inputs);
    network->run();
    printf("\nValue %f\n", network->getOutput()[0]);

    inputs->empty();
    inputs->addLast(1.0);
    inputs->addLast(0.0);
    network->setInput(inputs);
    network->run();
    printf("\nValue %f\n", network->getOutput()[0]);

    // for (int i = 0; i < 10; i++) {
    //     inputs->empty();
    //     expectedOutputs->empty();
    //     double in1 = (double) (rand() % 2);
    //     double in2 = (double) (rand() % 2);
    //     in1 = in1 == 0.0 ? 0.01 : 0.99;
    //     in2 = in2 == 0.0 ? 0.01 : 0.99;
    //     inputs->addLast(in1);
    //     inputs->addLast(in2);
    //     expectedOutputs->addLast(in1 == in2 ? 0.01 : 0.99);
    //     network->setInput(inputs);
    //     network->run();
    //
    //     // network->print();
    //     // usleep(1000000);
    //
    //     printf("\n%d expected %f actual %f\n", i, *(expectedOutputs->getLast()), network->getOutput()[0]);
    // }
    // #################################################################################################################


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

    // KnowledgeParser* kp = new KnowledgeParser();
    // kp->readFile((char*) "./res/knl/Oort2.knl");
    //
    // LayeredPerceptronModelParser* lpmp = new LayeredPerceptronModelParser(2, 1, 2, 2);
    // // lpmp->readFile((char*) "./res/mdl/NEWtestLPM.mdl");
    // // lpmp->getModel()->print();
    // // lpmp->writeFile((char*) "./res/mdl/NEWtestLPM.mdl");
    //
    //
    // Vector<vector_size_t>* layerSizes = new Vector<vector_size_t>();
    // // Add input layer.
    // layerSizes->addLast(1296);
    //
    // // Add hidden layer.
    // layerSizes->addLast(5);
    // //
    // // // Add hidden layer.
    // // layerSizes->addLast(5);
    // //
    // // // Add hidden layer.
    // // layerSizes->addLast(5);
    //
    // // Add output layer.
    // layerSizes->addLast(3);
    //
    // LayeredPerceptronNetwork* nnn = new LayeredPerceptronNetwork(new LayeredPerceptronModel(layerSizes));
    // nnn->print();
    // lpmp->setModel(nnn->getModel());
    // lpmp->writeFile((char*) "./res/mdl/NEWtestLPM.mdl");
    // return 1;
    //
    // // Create the network.
    // // lpmp->setModel(nnn->getModel());
    // lpmp->readFile((char*) "./res/mdl/NEWtestLPM.mdl");
    // // LayeredPerceptronNetwork* nnn = new LayeredPerceptronNetwork(new LayeredPerceptronModel(layerSizes));
    // // LayeredPerceptronNetwork* nnn = new LayeredPerceptronNetwork(lpmp->getModel());
    //
    // double startTime = getTime();
    // printf("\noutput: %f %f %f\n", nnn->getOutput()[0], nnn->getOutput()[1], nnn->getOutput()[2]);
    // // for (uint i = 0; i < 1000; i++) {
    // //     nnn->setInput(kp->getKnowledge()->getExperience(0)->getInputs());
    // //     nnn->setExpectedOutput(kp->getKnowledge()->getExperience(0)->getOutputs());
    // //     nnn->run();
    // //     // nnn->print();
    // //     nnn->correct();
    // // }
    // nnn->setInput(kp->getKnowledge()->getExperience(0)->getInputs());
    // nnn->run();
    // // nnn->print();
    // // printf("\noutput: %f %f %f\n", nnn->getOutput()[0], nnn->getOutput()[1], nnn->getOutput()[2]);
    // // printf("\nexpected: %f %f %f\n", kp->getKnowledge()->getExperience(0)->getOutputs()[0], kp->getKnowledge()->getExperience(0)->getOutputs()[1], kp->getKnowledge()->getExperience(0)->getOutputs()[2]);
    // // printf("\ninputsNum %d outputsNum %d\n", kp->getKnowledge()->getInputsNum(), kp->getKnowledge()->getOutputsNum());
    // nnn->train(kp->getKnowledge(), 10);
    // double endTime = getTime();
    //
    // printf("\nTraining completed\nTotal training time %fs\n", endTime - startTime);
    // lpmp->setModel(nnn->getModel());
    // lpmp->writeFile((char*) "./res/mdl/NEWtestLPM.mdl");
    // printf("\noutput: %f %f %f\n", nnn->getOutput()[0], nnn->getOutput()[1], nnn->getOutput()[2]);
    //
    // // nnn->print();
    // for (int i = 0;; i++) {
    //     // if (i % 100 == 0) {
    //     //     nnn->print();
    //     // }
    //     nnn->run();
    //     // printf("\noutput: %f %f %f\n", nnn->getOutput()[0], nnn->getOutput()[1], nnn->getOutput()[2]);
    // }















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