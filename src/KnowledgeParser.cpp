#include "KnowledgeParser.h"

namespace Oort {
    const char KnowledgeParser::HEADER_SEPARATOR = ':';
    const char KnowledgeParser::PRIMARY_SEPARATOR = ':';
    const char KnowledgeParser::SECONDARY_SEPARATOR = ',';
    const uint8_t KnowledgeParser::HEADER_LENGTH = 3;

    KnowledgeParser::KnowledgeParser() {
        this->knowledge = nullptr;
    }

    KnowledgeParser::KnowledgeParser(Knowledge* knowledge) {
        this->knowledge = knowledge;
    }

    void KnowledgeParser::readFile(char* fileName) {
        FILE* inputFile = nullptr;
        uint8_t inputsNum = 0;
        uint8_t outputsNum = 0;
        uint8_t precision = 0;
        byte* header = (byte*) malloc(HEADER_LENGTH);
        byte* inputs = nullptr;
        byte* outputs = nullptr;

        // Open input file in binary mode.
        inputFile = fopen(fileName, "rb");

        // Check if the file was correctly opened.
        if (inputFile != nullptr) {
            // Read the header the size of each element is 1 byte.
            fread(header, HEADER_LENGTH, 1, inputFile);

            // Use values read from the header.
            inputsNum = header[0];
            outputsNum = header[1];
            precision = header[2];
            inputs = (byte*) malloc(precision * inputsNum);
            outputs = (byte*) malloc(precision * inputsNum);
            //TODO Check if arrays were successfully allocated.

            printf("\n%d, %d, %d\n", inputsNum, outputsNum, precision);

            // Read input values.
            fread(inputs, inputsNum, precision, inputFile);
            printf("\n%d, %d, %d, %d, %d, %d, %d, %d\n", inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6], inputs[7]);

            // Read output values.
            fread(outputs, outputsNum, precision, inputFile);
            printf("\n%d, %d\n", outputs[0], outputs[1]);





            // Close the file at the end of the read operation.
            fclose(inputFile);
        } else {
            // There was an error opening the file.
            printf("\n<KnowledgeParser::readFile()> Error opening file %s\n", fileName);
        }
    }

    // void KnowledgeParser::readFile(char* fileName) {
    //     std::ifstream inputFile;
    //     std::string line;
    //     vector_size_t inputsNum;
    //     vector_size_t outputsNum;
    //     std::vector<std::string> data;
    //     std::vector<std::string> lineValues;
    //     Vector<neuron_value_t>* inputValues;
    //     Vector<neuron_value_t>* outputValues;
    //
    //     // Open the file in read mode.
    //     inputFile.open(fileName);
    //
    //     // Check if the file was correctly opened.
    //     if (inputFile.is_open()) {
    //         // The file was successfully opened.
    //         for (uint32_t i = 0; std::getline(inputFile, line); i++) {
    //             if (i <= 0) {
    //                 // The first line of the file is a header containing two values separated by a comma, indicating inputs
    //                 // size and outputs size.
    //
    //                 // Split the string based on the values separator.
    //                 data = splitString(line, HEADER_SEPARATOR);
    //                 // Create a knowledge object passing values read from the first line of the knowledge file.
    //                 this->knowledge = new Knowledge(std::stoi(data[0]), std::stoi(data[1]));
    //             } else {
    //                 // The other lines of the file are knowledge data, so create an experience object for every line and
    //                 // add it to the knowledge object.
    //
    //                 // Split the line by input-output separator and then separate outputs and inputs to create the
    //                 // experience.
    //                 data = splitString(line, PRIMARY_SEPARATOR);
    //                 inputValues = new Vector<neuron_value_t>();
    //                 outputValues = new Vector<neuron_value_t>();
    //
    //                 // Loop through input values (data[0]).
    //                 lineValues = splitString(data[0], SECONDARY_SEPARATOR);
    //                 for (std::string inString : lineValues) {
    //                     inputValues->addLast(std::stof(inString));
    //                 }
    //
    //                 // Loop through output values (data[1]).
    //                 lineValues = splitString(data[1], SECONDARY_SEPARATOR);
    //                 for (std::string outString : lineValues) {
    //                     outputValues->addLast(std::stof(outString));
    //                 }
    //
    //                 // Create an experience object based on read values and add it to the knowledge.
    //                 this->knowledge->addExperience(new Experience(inputValues, outputValues));
    //
    //             }
    //         }
    //
    //         // Close the file at the end of the read operation.
    //         inputFile.close();
    //     } else {
    //         // There was an error opening the file.
    //         printf("\n<KnowledgeParser::readFile()> Error opening file %s\n", fileName);
    //     }
    //     return;
    // }

    void KnowledgeParser::writeFile(char* fileName) {
        std::ofstream outputFile;
        std::string line;
        std::stringstream lineStream;

        if (this->knowledge) {
            // Open the file in write mode.
            // std::ofstream::open() automatically creates the file if not alredy present, so there's no need to check for its
            // existence.
            outputFile.open(fileName);

            // Check if the file was correctly opened.
            if (outputFile.is_open()) {
                // The file was successfully opened.
                // Write the header.
                outputFile << this->knowledge->getInputsNum() << HEADER_SEPARATOR << this->knowledge->getOutputsNum() << std::endl;

                // Loop through each experience in knowledge: each experience is a line of the output file.
                for (vector_size_t i = 0; i < this->knowledge->getExperiencesNum(); i++) {
                    // Empty the line to create a new one.
                    line = "";

                    // Loop through the inputs of the single experience to write them on the line.
                    for (vector_size_t j = 0; j < this->knowledge->getInputsNum(); j++) {
                        line += std::to_string(this->knowledge->getExperience(i)->getInput(j));

                        // Add SECONDARY_SEPARATOR between each input.
                        if (j != this->knowledge->getInputsNum() - 1) {
                            line += SECONDARY_SEPARATOR;
                        }
                    }

                    // Add PRIMARY_SEPARATOR between inputs and outputs.
                    line += PRIMARY_SEPARATOR;

                    // Loop through the outputs of the single experience to write them on the line.
                    for (vector_size_t j = 0; j < this->knowledge->getOutputsNum(); j++) {
                        line += std::to_string(this->knowledge->getExperience(i)->getOutput(j));

                        // Add SECONDARY_SEPARATOR between each output.
                        if (j != this->knowledge->getOutputsNum() - 1) {
                            line += SECONDARY_SEPARATOR;
                        }
                    }

                    // Write the line to the output file.
                    outputFile << line << std::endl;
                }

                // Close the file at the end of the write operation.
                outputFile.close();
            } else {
                // There was an error opening the file.
                printf("\n<KnowledgeParser::writeFile()> Error opening file %s\n", fileName);
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
}
