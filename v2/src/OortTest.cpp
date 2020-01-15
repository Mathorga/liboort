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
        printf("%f\t%f\t%f\t%f\t%f\n", i, math::sigmoid(i), math::fsigmoid(i), math::dsigmoid(i), math::dfsigmoid(i));
    }


    sTime = getNanoTime();
    for (double i = -1000.0; i < 1000.0; i += 0.001) {
        math::sigmoid(i);
    }
    eTime = getNanoTime();
    sigmTime = eTime - sTime;

    sTime = getNanoTime();
    for (double i = -1000.0; i < 1000.0; i += 0.001) {
        math::fsigmoid(i);
    }
    eTime = getNanoTime();
    fSigmTime = eTime - sTime;

    sTime = getNanoTime();
    for (double i = -1000.0; i < 1000.0; i += 0.001) {
        math::dsigmoid(i);
    }
    eTime = getNanoTime();
    dSigmTime = eTime - sTime;

    sTime = getNanoTime();
    for (double i = -1000.0; i < 1000.0; i += 0.001) {
        math::dfsigmoid(i);
    }
    eTime = getNanoTime();
    dFSigmTime = eTime - sTime;

    printf("\nSigmoid %f\nFast Sigmoid %f\nSigmoid Der %f\nFast Sigmoid Der %f\n", sigmTime / 1000000, fSigmTime / 1000000, dSigmTime / 1000000, dFSigmTime / 1000000);

    math::dtensor2d t;
    t.width = 5;
    t.height = 4;
    t.values = (double*) malloc(t.width * t.height * sizeof(double));
    for (uint32_t i = 0; i < t.width * t.height; i++) {
        t.values[i] = i;
    }
    print(t);

    // dtensor2d sigm;
    // sigm.width = 5;
    // sigm.height = 4;
    // sigm.values = (double*) malloc(t.width * t.height * sizeof(double));
    // sigmoid(sigm, t);
    // print(sigm);

    math::dtensor2d t2;
    t2.width = 4;
    t2.height = 5;
    t2.values = (double*) malloc(t2.width * t2.height * sizeof(double));
    for (uint32_t i = 0; i < t2.width * t2.height; i++) {
        t2.values[i] = i;
    }
    print(t2);

    int df = 0;
    math::dtensor2d res;
    res.width = 4;
    res.height = 4;
    res.values = (double*) malloc(res.width * res.height * sizeof(double));
    df = math::mul(res, t, t2);
    print(res);

    printf("\nSizeof tensor1d %luB\t%d\n", sizeof(t), df);

    return 0;
}
