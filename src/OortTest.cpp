#include "math.h"
#include "DenseLayer.h"
#include "Pooling2DLayer.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    Layer* testLayer = new Pooling2DLayer(6, 6, 1, 3, 3);
    math::dtensor testInput;
    math::alloc(&testInput, 6 * 6);
    math::rinit(testInput, 1.0);
    // utils::print(testInput);
    testLayer->step(testInput);

    return 0;
}
