#include "math.h"
#include "DenseLayer.h"
#include "Pooling2DLayer.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    // Layer* testLayer = new DenseLayer(2, 4);
    // math::dtensor testInput;
    // math::alloc(&testInput, 2);
    // // math::rinit(testInput, 1.0);
    // math::init(testInput, 0.5);
    // utils::print(testInput);
    // testLayer->step(testInput);
    // testLayer->print();

    math::dtensor3d testTensor;
    math::alloc(&testTensor, 3, 4, 2);
    math::rinit(testTensor, 10);

    utils::print(testTensor);

    printf("\nValue at index %d %d %d %.8f\n", 1, 2, 0, testTensor.values[IDX3D(1, 2, 0, 3, 4)]);

    return 0;
}
