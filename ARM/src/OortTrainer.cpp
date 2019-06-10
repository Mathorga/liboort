#include <dirent.h>
#include <algorithm>
#include "utils.h"

int main(int argc, char const *argv[]) {
    char* knowledgePath = nullptr;
    std::string fileName = "";
    std::string tmpFileName = "";
    std::string formatDelimiter = ".";
    std::string valuesDelimiter = "_";
    float value = 0;
    DIR* knowledgeDir = nullptr;
    struct dirent *entry = nullptr;
    size_t pos = 0;

    // Input check.
    if (argc > 2 || argc <= 1) {
        printf("Usage: %s [knowledgePath]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        knowledgePath = (char*) argv[1];
    }

    printf("\nKnowledge directory: %s\n", knowledgePath);

    // Open directory to read all files.
    knowledgeDir = opendir(knowledgePath);
    if (knowledgeDir != nullptr) {
        // Read all files and directories.
        while ((entry = readdir(knowledgeDir))) {
            fileName = entry->d_name;
            if (std::count(fileName.begin(), fileName.end(), valuesDelimiter.c_str()[0]) == 2 &&
                std::count(fileName.begin(), fileName.end(), formatDelimiter.c_str()[0]) == 1) {
                std::cout << fileName << std::endl;
                tmpFileName = fileName;

                // Get all values from the name.
                while ((pos = tmpFileName.find(valuesDelimiter)) != std::string::npos) {
                    value = atof(("0." + tmpFileName.substr(0, 4)).c_str());
                    printf("\n%f\n", value);
                    tmpFileName.erase(0, pos + valuesDelimiter.length());
                }
                value = atof(("0." + tmpFileName.substr(0, 4)).c_str());
                printf("\n%f\n", value);

                //TODO Open the file and manage it.
                std::cout << fileName << std::endl;
            }

            // while ((pos = fileName.find(formatDelimiter)) != std::string::npos) {
            //     value = fileName.substr(0, pos);
            //     std::cout << value << std::endl;
            //     fileName.erase(0, pos + formatDelimiter.length());
            // }
        }
    }

    closedir(knowledgeDir);

    return 0;
}
