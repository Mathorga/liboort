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
        byte* modelHeader = (byte*) malloc(TOTAL_NEURONS_NUM_DEPTH +
                                           INPUT_NEURONS_NUM_DEPTH +
                                           OUTPUT_NEURONS_NUM_DEPTH +
                                           NEURON_ID_DEPTH_DEPTH +
                                           NEURON_TYPE_DEPTH_DEPTH +
                                           NEURON_SYNAPSES_NUM_DEPTH +
                                           SYNAPSE_WEIGHT_DEPTH);
        vector_size_t neuronsNum = 0;
        vector_size_t inputNeuronsNum = 0;
        vector_size_t outputNeuronsNum = 0;
        uint8_t neuronIdDepth = 0;
        uint8_t neuronTypeDepth = 0;
        uint8_t synapsesNumDepth = 0;
        uint8_t synapseWeightDepth = 0;

        byte* reading = nullptr;
        uint32_t currentValue = 0;
        uint32_t currentNeuronId = 0;
        uint32_t currentNeuronType = 0;
        uint32_t currentSynapsesNum = 0;
        uint32_t currentSynapseInputNeuronId = 0;
        uint32_t currentSynapseWeight = 0;

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

            // Create the model according to the layers definition read from the file.
            this->model = new LayeredPerceptronModel(layerSizes);

            // Open Model file in binary read mode.
            modelFile = fopen(fileName, "rb");

            if (modelFile != nullptr) {
                // Model file is open, so read model from it.

                // Read header.
                fread(modelHeader, TOTAL_NEURONS_NUM_DEPTH +
                                   INPUT_NEURONS_NUM_DEPTH +
                                   OUTPUT_NEURONS_NUM_DEPTH +
                                   NEURON_ID_DEPTH_DEPTH +
                                   NEURON_TYPE_DEPTH_DEPTH +
                                   NEURON_SYNAPSES_NUM_DEPTH +
                                   SYNAPSE_WEIGHT_DEPTH, 1, modelFile);

                neuronsNum = byteArrayToUint(modelHeader, TOTAL_NEURONS_NUM_DEPTH);
                inputNeuronsNum = byteArrayToUint(&modelHeader[TOTAL_NEURONS_NUM_DEPTH], INPUT_NEURONS_NUM_DEPTH);
                outputNeuronsNum = byteArrayToUint(&modelHeader[TOTAL_NEURONS_NUM_DEPTH +
                                                                INPUT_NEURONS_NUM_DEPTH], OUTPUT_NEURONS_NUM_DEPTH);
                neuronIdDepth = byteArrayToUint(&modelHeader[TOTAL_NEURONS_NUM_DEPTH +
                                                             INPUT_NEURONS_NUM_DEPTH +
                                                             OUTPUT_NEURONS_NUM_DEPTH], NEURON_ID_DEPTH_DEPTH);
                neuronTypeDepth = byteArrayToUint(&modelHeader[TOTAL_NEURONS_NUM_DEPTH +
                                                               INPUT_NEURONS_NUM_DEPTH +
                                                               OUTPUT_NEURONS_NUM_DEPTH +
                                                               NEURON_ID_DEPTH_DEPTH], NEURON_TYPE_DEPTH_DEPTH);
                synapsesNumDepth = byteArrayToUint(&modelHeader[TOTAL_NEURONS_NUM_DEPTH +
                                                                      INPUT_NEURONS_NUM_DEPTH +
                                                                      OUTPUT_NEURONS_NUM_DEPTH +
                                                                      NEURON_ID_DEPTH_DEPTH +
                                                                      NEURON_TYPE_DEPTH_DEPTH], NEURON_SYNAPSES_NUM_DEPTH);
                synapseWeightDepth = byteArrayToUint(&modelHeader[TOTAL_NEURONS_NUM_DEPTH +
                                                                  INPUT_NEURONS_NUM_DEPTH +
                                                                  OUTPUT_NEURONS_NUM_DEPTH +
                                                                  NEURON_ID_DEPTH_DEPTH +
                                                                  NEURON_TYPE_DEPTH_DEPTH +
                                                                  NEURON_SYNAPSES_NUM_DEPTH], SYNAPSE_WEIGHT_DEPTH);

                printf("\n%d %d %d %d %d %d %d\n", neuronsNum, inputNeuronsNum, outputNeuronsNum, neuronIdDepth, neuronTypeDepth, synapsesNumDepth, synapseWeightDepth);

                // Read content.
                // Loop through neurons.
                for (vector_size_t i = 0; i < neuronsNum; i++) {
                    // Read neuron id.
                    reading = (byte*) malloc(neuronIdDepth);
                    fread(reading, neuronIdDepth, 1, modelFile);
                    currentNeuronId = byteArrayToUint(reading, neuronIdDepth);
                    free(reading);

                    // Read neuron type.
                    reading = (byte*) malloc(neuronTypeDepth);
                    fread(reading, neuronTypeDepth, 1, modelFile);
                    currentNeuronType = byteArrayToUint(reading, neuronTypeDepth);
                    free(reading);

                    // Read synapses number.
                    reading = (byte*) malloc(synapsesNumDepth);
                    fread(reading, synapsesNumDepth, 1, modelFile);
                    currentSynapsesNum = byteArrayToUint(reading, synapsesNumDepth);
                    free(reading);

                    printf("\n%d %d %d\n", currentNeuronId, currentNeuronType, currentSynapsesNum);

                    // Loop through synapses.
                    for (vector_size_t j = 0; j < currentSynapsesNum; j++) {
                        // Read synapse's input neuron id.
                        reading = (byte*) malloc(neuronIdDepth);
                        fread(reading, neuronIdDepth, 1, modelFile);
                        currentSynapseInputNeuronId = byteArrayToUint(reading, neuronIdDepth);
                        free(reading);

                        // Read synapse's weight.
                        reading = (byte*) malloc(synapseWeightDepth);
                        fread(reading, synapseWeightDepth, 1, modelFile);
                        currentSynapseWeight = byteArrayToUint(reading, synapseWeightDepth);
                        free(reading);

                        printf("\n\t%d %d\n", currentSynapseInputNeuronId, currentSynapseWeight);
                    }
                }


                // while(!feof(modelFile)) {
                //     reading = (byte*) malloc();
                //     fread(inputs, depth, inputsNum, inputFile);
                //
                //     // Manage EOF.
                //     // Read a byte from the file.
                //     fgetc(inputFile);
                //
                //     // Check if EOF is reached.
                //     if (!feof(inputFile)) {
                //         // If not EOF put back the stream pointer of the file.
                //         fseek(inputFile, -1, SEEK_CUR);
                //     }
                // }
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
