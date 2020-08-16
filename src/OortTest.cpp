#include "math.h"
#include "DenseLayer.h"
#include "Pooling2DLayer.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    Layer* testLayer = new Pooling2DLayer(10, 10, 1, 2, 2);
    math::dtensor testInput;
    math::alloc(&testInput, 10 * 10);
    math::rinit(testInput, 1.0);
    // utils::print(testInput);
    testLayer->step(testInput);

    return 0;
}
