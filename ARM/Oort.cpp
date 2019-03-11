#include "Nerve.h"
#include "SimpleBrain.h"
#include "utils.h"

#define INPUT_NUM 1024
#define OUTPUT_NUM 2

int main(int argc, char const *argv[]) {
    double startTime = 0;
    double endTime = 0;
    double execTime = 0;

    double *input = (double *) malloc(INPUT_NUM * sizeof(double));
    double *output;

    SimpleBrain *brain = new SimpleBrain(INPUT_NUM, OUTPUT_NUM);

    // Main loop of the program.
    for (uint16_t i = 0;; i ++) {
        //TODO Get input from the nerve.

        // Set input to the brain.
        // brain->setInput(input);

        // Run the brain.
        startTime = getNanoTime();
        brain->run();
        endTime = getNanoTime();
        execTime = endTime - startTime;

        // Get output from the brain.
        output = brain->getOutput();

        //TODO Send output to the nerve.
    }

    return 0;
}
