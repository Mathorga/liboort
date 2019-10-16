#include "LayeredPerceptronModelParser.h"

namespace Oort {
    const uint8_t LayeredPerceptronModelParser::LYR_VALUE_DEPTH = 4;

    void LayeredPerceptronModelParser::readFile(char* fileName) {
        FILE* modelFile = nullptr;
        FILE* layerFile = nullptr;
        char* layerFileName = (char*) malloc(256);
        byte* layersVal = (byte*) malloc(LYR_VALUE_DEPTH);
        Vector<vector_size_t>* layerSizes = new Vector<vector_size_t>();
        uint8_t layersNum = 0;

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
<<<<<<< HEAD

            // Read layers number.
            fread(layersVal, LYR_VALUE_DEPTH, 1, layerFile);
            layersNum = byteArrayToUint(layersVal, LYR_VALUE_DEPTH);

            // Read each layer's size.
            for (uint32_t i = 0; i < layersNum; i++) {
                //TODO Check if the file is consistent in length with the specified layers number.

                // Read layer size and add it to the configuration.
                fread(layersVal, LYR_VALUE_DEPTH, 1, layerFile);
                layerSizes->addLast(byteArrayToUint(layersVal, LYR_VALUE_DEPTH));
            }
=======
            //TODO Read and store layer configuration for the model.
>>>>>>> 94984dba106aea55332860f3e67ab37bee949a54

            // Open Model file in binary read mode.
            modelFile = fopen(fileName, "rb");

            if (modelFile != nullptr) {
                // Model file is open, so read model from it.
                //TODO Read and store model.

                // Create the model.
                this->model = new LayeredPerceptronModel(layerSizes);
            } else {
                // There was an error opening the Model file.
                printf("\n<LayeredPerceptronModelParser::readFile()> Error: could not open Model file %s\n", fileName);
            }

            // Close the model file stream in order not to keep it locked.
            fclose(modelFile);
        } else {
            // There was an error opening the Layer file.
            printf("\n<LayeredPerceptronModelParser::readFile()> Error: could not open Layer file %s\n", layerFileName);
        }

        // Close the model file stream in order not to keep it locked.
        fclose(layerFile);
    }

    void LayeredPerceptronModelParser::writeFile(char* fileName) {

    }

    LayeredPerceptronModel* LayeredPerceptronModelParser::getModel() {
        return this->model;
    }

    void LayeredPerceptronModelParser::setModel(LayeredPerceptronModel* inputModel) {

    }
}
