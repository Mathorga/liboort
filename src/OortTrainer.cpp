#include "utils.h"
#include "SparsePerceptronNetwork.h"
#include "SparsePerceptronModelParser.h"
#include "KnowledgeParser.h"

#define DEFAULT_ITERATIONS_NUM 100

using namespace Oort;

int main(int argc, const char* argv[]) {
    char* modelFileName = nullptr;
    char* knowledgeFileName = nullptr;
    uint32_t iterationsNum = 0;
    SparsePerceptronModelParser* modelParser = new SparsePerceptronModelParser();
    KnowledgeParser* knowledgeParser = new KnowledgeParser();
    SparsePerceptronNetwork* network = nullptr;
    double startTime = 0.0;
    double endTime = 0.0;


    // Input check.
    if (argc > 4 || argc <= 2) {
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

    if (iterationsNum == 0) {
        iterationsNum = DEFAULT_ITERATIONS_NUM;
    }

    // Read model file and create network out of it.
    printf("\nReading mdl file %s\n", modelFileName);
    modelParser->readFile(modelFileName);
    // modelParser->getModel()->print();
    printf("\nCreated network\n");
    network = new SparsePerceptronNetwork(modelParser->getModel());

    // Read knowledge file.
    printf("\nReading knl file %s\n", knowledgeFileName);
    knowledgeParser->readFile(knowledgeFileName);
    printf("\nRunning network training for %d iterations\n", iterationsNum);
    startTime = getTime();
    network->train(knowledgeParser->getKnowledge(), iterationsNum);
    endTime = getTime();
    printf("\nTraining completed\nTotal training time %fs\n", endTime - startTime);

    modelParser->setModel(network->getModel());
    modelParser->writeFile((char*) "./res/mdl/trained.mdl");
}
