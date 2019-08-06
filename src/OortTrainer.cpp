#include "utils.h"
#include "SparsePerceptronNetwork.h"
#include "SparsePerceptronModelParser.h"
#include "KnowledgeParser.h"

using namespace Oort;

int main(int argc, const char* argv[]) {
    char* modelFileName = nullptr;
    char* knowledgeFileName = nullptr;
    uint32_t iterationsNum = 0;
    SparsePerceptronModelParser* modelParser = new SparsePerceptronModelParser();
    KnowledgeParser* knowledgeParser = new KnowledgeParser();
    SparsePerceptronNetwork* network = nullptr;


    // Input check.
    if (argc != 4) {
        printf("Usage: %s [modelFileName] [knowledgeFileName] [iterationsNum]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        modelFileName = (char*) argv[1];
    }
    if (argc > 2) {
        knowledgeFileName = (char*) argv[2];
    }
    if (argc > 3) {
        iterationsNum = atoi(argv[3]);
    }

    // Read model file and create network out of it.
    modelParser->readFile(modelFileName);
    printf("\nRead mdl file\n");
    // modelParser->getModel()->print();
    network = new SparsePerceptronNetwork(modelParser->getModel());
    printf("\nCreated network\n");

    // Read knowledge file.
    knowledgeParser->readFile(knowledgeFileName);
    printf("\nRead knl file\n");
    network->train(knowledgeParser->getKnowledge(), iterationsNum);
    network->print();

    printf("\nModel Path: %s\n", modelFileName);
    printf("\nKnowledge Path: %s\n", knowledgeFileName);
    printf("\nIterations: %d\n", iterationsNum);

}
