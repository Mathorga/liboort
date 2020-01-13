#include "Model.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    array_size_t layerSizes[3] = {2, 4, 1};

    Model* testGraph = new Model(3, layerSizes);

    double sigmTime = 0.0;
    double fSigmTime = 0.0;
    double dSigmTime = 0.0;
    double dFSigmTime = 0.0;
    double sTime = 0.0;
    double eTime = 0.0;

    for (double i = -10.0; i < 10.0; i += 0.01) {
        printf("%f\t%f\t%f\t%f\t%f\n", i, sigmoid(i), fsigmoid(i), dsigmoid(i), dfsigmoid(i));
    }


    sTime = getNanoTime();
    for (double i = -1000.0; i < 1000.0; i += 0.001) {
        sigmoid(i);
    }
    eTime = getNanoTime();
    sigmTime = eTime - sTime;

    sTime = getNanoTime();
    for (double i = -1000.0; i < 1000.0; i += 0.001) {
        fsigmoid(i);
    }
    eTime = getNanoTime();
    fSigmTime = eTime - sTime;

    sTime = getNanoTime();
    for (double i = -1000.0; i < 1000.0; i += 0.001) {
        dsigmoid(i);
    }
    eTime = getNanoTime();
    dSigmTime = eTime - sTime;

    sTime = getNanoTime();
    for (double i = -1000.0; i < 1000.0; i += 0.001) {
        dfsigmoid(i);
    }
    eTime = getNanoTime();
    dFSigmTime = eTime - sTime;

    printf("\nSigmoid %f\nFast Sigmoid %f\nSigmoid Der %f\nFast Sigmoid Der %f\n", sigmTime / 1000000, fSigmTime / 1000000, dSigmTime / 1000000, dFSigmTime / 1000000);

    return 0;
}
