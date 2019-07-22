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
    std::string lineValue;
    vector_size_t inputsNum;
    vector_size_t outputsNum;
    std::vector<std::string> data

    // Open the file in read mode.
    inputFile.open(fileName);
    // Check if the file was correctly opened.
    if (inputFile.is_open()) {
        // The file was successfully opened.
        for (uint32_t i = 0; std::getline(inputFile, line); i++) {
    //         std::istringstream lineStream(line);
            if (i <= 0) {
                // The first line of the file is a header containing two values separated by a comma, indicating inputs
                // size and outputs size.
                data = splitString(line, ',');
                this->knowledge = new Knowledge(std::stoi(data[0]), std::stoi(data[1]));
    //             for (uint8_t j = 0; std::getline(lineStream, lineValue, ','), j++) {
    //                 if (j <= 0) {
    //                     inputsNum = std::stoi(lineValue);
    //                 } else if (j >= 1) {
    //                     outputsNum = std::stoi(lineValue);
    //                 }
    //             }
    //             // Create data based on read values.
    //             this->data = new Knowledge(inputsNum, outputsNum);
    //         } else {
    //             // The other lines of the file are knowledge data.
    //
    //         }
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

void KnowledgeParser::setData(Knowledge* knowledge) {
    this->knowledge = knowledge;
}
