#include "math.h"
#include "DenseLayer.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    printf("\nHERE\n");
    Layer* testLayer = new DenseLayer(2, 4);
    math::dtensor1d testInput;
    math::rinit(testInput, 1.0);
    // utils::print(testInput);
    //testLayer->step(testInput);
    // testLayer->print();

    return 0;
}
