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

    // math::dtensor3d t3D;
    // math::alloc(&t3D, 4, 4, 2);
    // math::rinit(t3D, 10);
    // utils::print(t3D);
    // printf("\nValue at index %d %d %d %.8f\n", 1, 2, 1, t3D.values[IDX3D(1, 2, 1, t3D.width, t3D.height)]);

    // math::dtensor2d t2D;
    // math::alloc(&t2D, 3, 4);
    // math::rinit(t2D, 10);
    // utils::print(t2D);
    // printf("\nValue at index %d %d %.8f\n", 1, 2, t2D.values[IDX2D(1, 2, t2D.width)]);

    Layer* testLayer = new Pooling2DLayer(4, 4, 1, 2, 2);
    math::dtensor testInput;
    math::alloc(&testInput, 4 * 4);
    math::rinit(testInput, 1.0);
    utils::print(testInput);
    testLayer->step(testInput);

    return 0;
}
