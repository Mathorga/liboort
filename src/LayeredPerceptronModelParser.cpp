#include "LayeredPerceptronModelParser.h"

namespace Oort {
    const uint8_t LayeredPerceptronModelParser::LYR_VALUE_DEPTH = 4;

    void LayeredPerceptronModelParser::readFile(char* fileName) {
        FILE* modelFile = nullptr;
        FILE* layerFile = nullptr;
        char* layerFileName = (char*) malloc(256);

        // Check if file extension is right.
        // The file extension doesn't have to be right, but it's used as a warning that the file could be the wrong
        // format.
        if (strstr(fileName, ".mdl") == nullptr) {
            // Warning: the file might not be the right format.
            printf("\n<LayeredPerceptronModelParser::readFile()> Warning: file doesn't have a .mdl extension\n");
        }

        // Copy model file name to layer file name, because the layer file needs to have the same name as the model
        // file.
        strcpy(layerFileName, fileName);

        // Add the .lyr extension to find the correct file.
        // Model Layer files necessarily need to have the right extension in order to be recognized.
        strncat(layerFileName, ".lyr", 4);

        // Open Model Layer file in binary read mode.
        layerFile = fopen(layerFileName, "rb");

        if (layerFile != nullptr) {
            // Layer file is open, so read informations from it.
            //TODO Read and store layer configuration for the model.

            // Open Model file in binary read mode.
            modelFile = fopen(fileName, "rb");

            if (modelFile != nullptr) {
                // Model file is open, so read model from it.
                //TODO Read and store model.
            } else {
                // There was an error opening the Model file.
                printf("\n<LayeredPerceptronModelParser::readFile()> Error: could not open Model file %s\n", fileName);
            }
        } else {
            // There was an error opening the Layer file.
            printf("\n<LayeredPerceptronModelParser::readFile()> Error: could not open Layer file %s\n", layerFileName);
        }
    }

    void LayeredPerceptronModelParser::writeFile(char* fileName) {

    }

    LayeredPerceptronModel* LayeredPerceptronModelParser::getModel() {

    }

    void LayeredPerceptronModelParser::setModel(LayeredPerceptronModel* inputModel) {

    }
}
