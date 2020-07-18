#include "math.h"
#include "DenseLayer.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    Layer* testLayer = new DenseLayer(2, 4);
    math::dtensor testInput;
    math::alloc(&testInput, 2);
    math::rinit(testInput, 1.0);
    utils::print(testInput);
    testLayer->step(testInput);
    // testLayer->print();

    return 0;
}
