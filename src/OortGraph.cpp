#include "NeuralGraph.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    array_size_t layerSizes[3] = {2, 4, 1};

    NeuralGraph* testGraph = new NeuralGraph(3, layerSizes);

    return 0;
}
