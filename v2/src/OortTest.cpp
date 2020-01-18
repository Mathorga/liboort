#include "Model.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    array_size_t layerSizes[3] = {2, 4, 1};

    Model* testGraph = new Model(3, layerSizes);

    math::dtensor1d inputs;
    math::alloc(&inputs, 2);
    inputs.values[0] = 0;
    inputs.values[1] = 1;

    double sTime = 0.0;
    double eTime = 0.0;

    return 0;
}
