#include "KnowledgeParser.h"

KnowledgeParser::KnowledgeParser() {
    this->knowledge = nullptr;
}

KnowledgeParser::KnowledgeParser(Knowledge* knowledge) {
    this->knowledge = knowledge;
}

void KnowledgeParser::readFile(char* fileName) {
    std::ifstream inputFile;
    std::string line;
    vector_size_t inputsNum;
    vector_size_t outputsNum;
    std::vector<std::string> data;
    std::vector<std::string> lineValues;
    Vector<neuron_value_t>* inputValues;
    Vector<neuron_value_t>* outputValues;

    // Open the file in read mode.
    inputFile.open(fileName);
    // Check if the file was correctly opened.
    if (inputFile.is_open()) {
        // The file was successfully opened.
        for (uint32_t i = 0; std::getline(inputFile, line); i++) {
            if (i <= 0) {
                // The first line of the file is a header containing two values separated by a comma, indicating inputs
                // size and outputs size.

                // Split the string based on the values separator.
                data = splitString(line, ',');
                // Create a knowledge object passing values read from the first line of the knowledge file.
                this->knowledge = new Knowledge(std::stoi(data[0]), std::stoi(data[1]));
            } else {
                // The other lines of the file are knowledge data, so create an experience object for every line and
                // add it to the knowledge object.

                // Split the line by input-output separator and then separate outputs and inputs to create the
                // experience.
                data = splitString(line, ';');
                inputValues = new Vector<neuron_value_t>();
                outputValues = new Vector<neuron_value_t>();

                // Loop through input values (data[0]).
                lineValues = splitString(data[0], ',');
                for (std::string inString : lineValues) {
                    inputValues->addLast(std::stof(inString));
                }

                // Loop through output values (data[1]).
                lineValues = splitString(data[1], ',');
                for (std::string outString : lineValues) {
                    outputValues->addLast(std::stof(outString));
                }

                // Create an experience object based on read values and add it to the knowledge.
                this->knowledge->addExperience(new Experience(inputValues, outputValues));

            }
        }
        // Close the file at the end of the read operation.
        inputFile.close();
    } else {
        printf("\n<KnowledgeParser::readFile()> Error opening file %s\n", fileName);
    }
    return;
}

void KnowledgeParser::writeFile(char* fileName) {
    return;
}

Knowledge* KnowledgeParser::getKnowledge() {
    return this->knowledge;
}

void KnowledgeParser::setKnowledge(Knowledge* knowledge) {
    this->knowledge = knowledge;
}
