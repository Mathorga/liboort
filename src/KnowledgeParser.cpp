#include "KnowledgeParser.h"

namespace Oort {
    const uint8_t KnowledgeParser::HEADER_LENGTH = 9;
    const uint8_t KnowledgeParser::INPUTS_NUM_DEPTH = 4;
    const uint8_t KnowledgeParser::OUTPUTS_NUM_DEPTH = 4;
    const uint8_t KnowledgeParser::DEFAULT_VALUE_DEPTH = 1;
    const uint8_t KnowledgeParser::MAX_VALUE_DEPTH = 4;

    KnowledgeParser::KnowledgeParser() {
        this->knowledge = nullptr;
        this->depth = 0;
    }

    KnowledgeParser::KnowledgeParser(Knowledge* knowledge) {
        this->knowledge = knowledge;
    }

    void KnowledgeParser::readFile(char* fileName) {
        FILE* inputFile = nullptr;
        uint32_t inputsNum = 0;
        uint32_t outputsNum = 0;
        uint8_t depth = 0;
        byte* header = (byte*) malloc(HEADER_LENGTH);
        byte* inputs = nullptr;
        byte* outputs = nullptr;
        Vector<neuron_value_t>* inputVector = new Vector<neuron_value_t>();
        Vector<neuron_value_t>* outputVector = new Vector<neuron_value_t>();
        uint32_t currentValue = 0;

        // Check if file extension is right.
        // The file extension doesn't have to be right, but it's used as a warning that the file could be the wrong
        // format.
        if (strstr(fileName, ".knl") == nullptr) {
            // Warning: the file might not be the right format.
            printf("\n<KnowledgeParser::readFile()> Warning: file doesn't have a .knl extension\n");
        }

        // Open input file in binary read mode.
        inputFile = fopen(fileName, "rb");

        // Check if the file was correctly opened.
        if (inputFile != nullptr) {
            // Read the header.
            fread(header, HEADER_LENGTH, 1, inputFile);

            // Use values read from the header.
            inputsNum = byteArrayToUint(header, INPUTS_NUM_DEPTH);
            outputsNum = byteArrayToUint(&header[INPUTS_NUM_DEPTH], OUTPUTS_NUM_DEPTH);
            depth = byteArrayToUint(&header[INPUTS_NUM_DEPTH + OUTPUTS_NUM_DEPTH], 1);

            // inputsNum = header[0];
            // outputsNum = header[1];
            // depth = header[2];

            // Create knowledge.
            this->knowledge = new Knowledge(inputsNum, outputsNum);

            while(!feof(inputFile)) {
                inputs = (byte*) malloc(depth * inputsNum);
                outputs = (byte*) malloc(depth * outputsNum);
                inputVector = new Vector<neuron_value_t>();
                outputVector = new Vector<neuron_value_t>();
                // inputVector->empty();
                // outputVector->empty();
                //TODO Check if arrays were successfully allocated.

                // Read input values.
                // The "inputs" variable contains all input values of the experience in binary format. Every value is
                // depth bytes long, so, in order to read the correct value some conversion is needed.
                // E.G.
                // Being depth = 2 and inputsNum = 4, the file may appear like so:
                // 04    01    02    FA    0C    64    40    5D    BB    D1    9E    1F    80
                // The first three bytes define the header, in order: inputs number, outputs number, depth.
                // The following bytes define inputs and outputs (in this case only one experience is shown).
                // Input values in this file are: fA0C, which becomes 64012 in decimal, 6440, 25664 in decimal, 5DBB
                // (23995) and D19E (53662). The double loop manages the binary to decimal conversion.
                // In order to use these values as neuron values, they need to be converted to real numbers. This is
                // what the last instruction of the outer loop does.
                fread(inputs, depth, inputsNum, inputFile);
                for (uint32_t i = 0; i < inputsNum; i++) {
                    // Convert byte array to integer.
                    currentValue = byteArrayToUint(&inputs[IDX(i, 0, depth)], depth);

                    // Convert integer to neuron value.
                    inputVector->addLast(currentValue / pow(2, depth * 8));
                }

                // Read output values.
                // For output values, the exact same process used for inputs is applied.
                fread(outputs, depth, outputsNum, inputFile);
                for (uint32_t i = 0; i < outputsNum; i++) {
                    // Convert byte array to integer.
                    currentValue = byteArrayToUint(&outputs[IDX(i, 0, depth)], depth);

                    // Convert integer to neuron value.
                    outputVector->addLast(currentValue / pow(2, depth * 8));
                }
                this->knowledge->addExperience(new Experience(inputVector, outputVector));
                free(inputs);
                free(outputs);

                // Manage EOF.
                // Read a byte from the file.
                fgetc(inputFile);

                // Check if EOF is reached.
                if (!feof(inputFile)) {
                    // If not EOF put back the stream pointer of the file.
                    fseek(inputFile, -1, SEEK_CUR);
                }
            }

            // Close the file at the end of the read operation.
            fclose(inputFile);
        } else {
            // There was an error opening the file.
            printf("\n<KnowledgeParser::readFile()> Error: could not open file %s\n", fileName);
        }
    }

    void KnowledgeParser::writeFile(char* fileName) {
        FILE* outputFile = nullptr;
        uint8_t depth = 0;
        byte* value = nullptr;
        // byte* value = (byte*) malloc(depth);
        uint32_t intValue = 0;

        // Check if depth was previously set. If not use the default one.
        if (this->depth == 0) {
            depth = DEFAULT_VALUE_DEPTH;
        } else {
            depth = this->depth;
        }

        // Check if knowledge was previously set. return if not.
        if (this->knowledge) {
            // Open the file in binary write mode.
            // fopen() automatically creates the file if not alredy present, so there's no need to check for its
            // existence.
            outputFile = fopen(fileName, "wb");

            // Check if the file was correctly opened.
            if (outputFile != nullptr) {
                // Write header.
                fwrite(uintToByteArray(this->knowledge->getInputsNum(), INPUTS_NUM_DEPTH), INPUTS_NUM_DEPTH, 1, outputFile);
                fwrite(uintToByteArray(this->knowledge->getOutputsNum(), OUTPUTS_NUM_DEPTH), OUTPUTS_NUM_DEPTH, 1, outputFile);
                // fputc(this->knowledge->getInputsNum(), outputFile);
                // fputc(this->knowledge->getOutputsNum(), outputFile);
                fputc(depth, outputFile);

                // Write knowledge data.
                // Loop through experiences.
                for (vector_size_t i = 0; i < this->knowledge->getExperiencesNum(); i++) {
                    // Write experience inputs.
                    for (vector_size_t j = 0; j < this->knowledge->getInputsNum(); j++) {

                        // Convert neuron value to integer value.
                        intValue = this->knowledge->getExperience(i)->getInput(j) * pow(2, depth * 8);

                        // Convert the value to a depth-long byte array.
                        value = uintToByteArray(intValue, depth);
                        // for (int16_t k = depth - 1; k >= 0; k--) {
                        //     value[k] = (intValue >> 8 * k) & 0xFF;
                        // }

                        fwrite(value, depth, 1, outputFile);
                    }

                    // Write experience outputs.
                    for (vector_size_t j = 0; j < this->knowledge->getOutputsNum(); j++) {
                        // Convert neuron value to integer value.
                        intValue = this->knowledge->getExperience(i)->getOutput(j) * pow(2, depth * 8);

                        // Convert the value to a depth-long byte array.
                        value = uintToByteArray(intValue, depth);
                        // for (int16_t k = depth - 1; k >= 0; k--) {
                        //     value[k] = (intValue >> 8 * k) & 0xFF;
                        // }

                        fwrite(value, depth, 1, outputFile);
                    }
                }

                // Close the file at the end of the write operation.
                fclose(outputFile);
            } else {
                // There was an error opening the file.
                printf("\n<KnowledgeParser::writeFile()> Error: file not opened %s\n", fileName);
            }
        } else {
            printf("\n<KnowledgeParser::writeFile()> Error: knowledge not set\n");
        }
        return;
    }

    Knowledge* KnowledgeParser::getKnowledge() {
        return this->knowledge;
    }

    void KnowledgeParser::setKnowledge(Knowledge* knowledge) {
        this->knowledge = knowledge;
    }

    void KnowledgeParser::setDepth(uint8_t depth) {
        this->depth = depth;
    }
}
