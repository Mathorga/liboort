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
        vector_size_t neuronId = 0;
        uint32_t neuronType = 0;
        vector_size_t synapsesNum = 0;
        vector_size_t synapseInputNeuronId = 0;
        synapse_weight_t synapseWeight = 0;

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

                // Check if model file is consistent with layer file.
                if (inputNeuronsNum == this->model->getInputsNum() &&
                    outputNeuronsNum == this->model->getOutputsNum()) {
                    // Read content.
                    // Loop through neurons.
                    for (vector_size_t i = 0; i < neuronsNum; i++) {
                        // Read neuron id.
                        reading = (byte*) malloc(neuronIdDepth);
                        fread(reading, neuronIdDepth, 1, modelFile);
                        neuronId = byteArrayToUint(reading, neuronIdDepth);
                        free(reading);

                        // Read neuron type.
                        reading = (byte*) malloc(neuronTypeDepth);
                        fread(reading, neuronTypeDepth, 1, modelFile);
                        neuronType = byteArrayToUint(reading, neuronTypeDepth);
                        free(reading);

                        // Check if neuron type is consistent with the created one.
                        if (this->model->getPerceptron(neuronId)->getType() == neuronType) {
                            // Read synapses number.
                            reading = (byte*) malloc(synapsesNumDepth);
                            fread(reading, synapsesNumDepth, 1, modelFile);
                            synapsesNum = byteArrayToUint(reading, synapsesNumDepth);
                            free(reading);

                            // Loop through synapses.
                            for (vector_size_t j = 0; j < synapsesNum; j++) {
                                // Read synapse's input neuron id.
                                reading = (byte*) malloc(neuronIdDepth);
                                fread(reading, neuronIdDepth, 1, modelFile);
                                synapseInputNeuronId = byteArrayToUint(reading, neuronIdDepth);
                                free(reading);

                                // Check if synapse input neuron is correct.
                                if (this->model->getPerceptron(neuronId)->getSynapse(j)->getInputNeuron()->getId() == synapseInputNeuronId) {
                                    // Read synapse's weight.
                                    reading = (byte*) malloc(synapseWeightDepth);
                                    fread(reading, synapseWeightDepth, 1, modelFile);
                                    synapseWeight = byteArrayToDouble(reading, synapseWeightDepth);
                                    free(reading);

                                    // Set the weight to the correct synapse.
                                    this->model->getPerceptron(neuronId)->getSynapse(j)->setWeight(synapseWeight);
                                } else {
                                    printf("\n<LayeredPerceptronModelParser::readFile()> Error: incorrect input neuron for synapse %d of neuron %d\n", j, neuronId);
                                }
                            }
                        } else {
                            // Neuron type is not consistent.
                            printf("\n<LayeredPerceptronModelParser::readFile()> Error: incorrect neuron type for perceptron id %d\n", neuronId);
                        }
                    }
                } else {
                    // Model file is not consistent with layer file.
                    printf("\n<LayeredPerceptronModelParser::readFile()> Error: inputs or outputs number not consistent between Model file %s and Layer file %s\n", fileName, layerFileName);
                }
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
        FILE* modelFile = nullptr;
        FILE* layerFile = nullptr;
        char* layerFileName = (char*) malloc(256);

        // Check if file extension is right.
        // The file extension doesn't have to be right, but it's used as a warning that the file could be the wrong
        // format.
        if (strstr(fileName, ".mdl") == nullptr) {
            // Warning: the file might not be the right format.
            printf("\n<LayeredPerceptronModelParser::writeFile()> Warning: file name doesn't have a .mdl extension\n");
        }

        // Copy model file name to layer file name, because the layer file needs to have the same name as the model
        // file.
        strcpy(layerFileName, fileName);

        // Add the .lyr extension to find the correct file.
        // Model Layer files necessarily need to have the right extension in order to be recognized.
        strncat(layerFileName, ".lyr", 4);

        printf("\n%s\n", layerFileName);

        // Check if model was previously set. return if not.
        if (this->model) {
            // Open the file in binary write mode.
            // fopen() automatically creates the file if not alredy present, so there's no need to check for its
            // existence.
            layerFile = fopen(layerFileName, "wb");

            // Check if the file was correctly opened.
            if (layerFile != nullptr) {
                // Write number of layers.
                fwrite(uintToByteArray(this->model->getLayersNum(), LYR_VALUE_DEPTH), LYR_VALUE_DEPTH, 1, layerFile);

                // Loop through layers of the model.
                for (vector_size_t i = 0; i < this->model->getLayersNum(); i++) {
                    // Write layer size.
                    fwrite(uintToByteArray(this->model->getLayer(i)->getSize(), LYR_VALUE_DEPTH), LYR_VALUE_DEPTH, 1, layerFile);
                }

                // Close the file at the end of the write operation.
                fclose(layerFile);
            }

            // Open the file in binary write mode.
            // fopen() automatically creates the file if not alredy present, so there's no need to check for its
            // existence.
            modelFile = fopen(fileName, "wb");

            // Check if the file was correctly opened.
            if (modelFile != nullptr) {
                // Close the file at the end of the write operation.
                fclose(modelFile);
            }
        } else {
            printf("\n<LayeredPerceptronModelParser::writeFile()> Error: model not set\n");
        }
    }

    LayeredPerceptronModel* LayeredPerceptronModelParser::getModel() {
        return this->model;
    }

    void LayeredPerceptronModelParser::setModel(LayeredPerceptronModel* inputModel) {
        this->model = inputModel;
    }
}
