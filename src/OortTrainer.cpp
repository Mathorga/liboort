#include "utils.h"

int main(int argc, const char* argv[]) {
    char* modelPath = nullptr;
    char* knowledgePath = nullptr;
    uint32_t iterationsNum = 0;

    // Input check.
    if (argc != 4) {
        printf("Usage: %s [modelPath] [knowledgePath] [iterationsNum]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        modelPath = (char*) argv[1];
    }
    if (argc > 2) {
        knowledgePath = (char*) argv[2];
    }
    if (argc > 3) {
        iterationsNum = atoi(argv[3]);
    }

    printf("\nModel Path: %s\n", modelPath);
    printf("\nKnowledge Path: %s\n", knowledgePath);
    printf("\nIterations: %d\n", iterationsNum);

}
