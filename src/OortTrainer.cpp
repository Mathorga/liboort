#include <dirent.h>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "utils.h"
#include "Synapse.h"
#include "SparsePerceptronModelParser.h"
#include "SparsePerceptronNetwork.h"

#define OUTPUTS_NUM 3
#define VALUE_PRECISION 4

using namespace cv;

void readValuesFromName(neuron_value_t* values, std::string fileName, std::string delimiter) {
    uint8_t index = 0;
    size_t pos = 0;

    while ((pos = fileName.find(delimiter)) != std::string::npos) {
        values[index] = atof(("0." + fileName.substr(0, VALUE_PRECISION)).c_str());
        fileName.erase(0, pos + delimiter.length());
        index++;
    }
    values[index] = atof(("0." + fileName.substr(0, 4)).c_str());
}

int main(int argc, char const *argv[]) {
    char* knowledgePath = nullptr;
    char* modelPath = nullptr;
    std::string fileName = "";
    std::string tmpFileName = "";
    std::string formatDelimiter = ".";
    std::string valuesDelimiter = "_";
    float value = 0;
    DIR* knowledgeDir = nullptr;
    struct dirent *entry = nullptr;
    neuron_value_t* values = (neuron_value_t*) malloc(OUTPUTS_NUM * sizeof(neuron_value_t));
    SparsePerceptronModelParser* parser = nullptr;
    SparsePerceptronNetwork* brain = nullptr;
    Mat image;

    // Input check.
    if (argc > 3 || argc <= 2) {
        printf("Usage: %s [modelFilePath] [knowledgeFilePath]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        modelPath = (char*) argv[1];
    }
    if (argc > 2) {
        knowledgePath = (char*) argv[2];
    }


    printf("\nKnowledge directory: %s\n", knowledgePath);


    parser = new SparsePerceptronModelParser();
    parser->readFile(modelPath);
    brain = new SparsePerceptronNetwork(parser->getModel());


    // Open directory to read all files.
    knowledgeDir = opendir(knowledgePath);
    if (knowledgeDir != nullptr) {
        // Read all files and directories.
        while ((entry = readdir(knowledgeDir))) {
            fileName = entry->d_name;
            // Only read well-named files.
            if (std::count(fileName.begin(), fileName.end(), valuesDelimiter.c_str()[0]) == 2 &&
                std::count(fileName.begin(), fileName.end(), formatDelimiter.c_str()[0]) == 1) {
                tmpFileName = fileName;

                // Get all values from the name.
                readValuesFromName(values, fileName, valuesDelimiter);

                // Set expected output obtained from the file name.
                brain->setExpectedOutput(values);

                //TODO Open the file and manage it.
                std::cout << fileName << std::endl;

                // Read file.
                image = imread(knowledgePath + fileName);

                // Read single pixels.
                for (int i = 0; i < image.rows; i++) {
                    for (int j = 0; j < image.cols; j++) {
                        // You can now access the pixel value with cv::Vec3b
                        std::cout << (int) image.at<Vec3b>(i,j)[0] << " " << (int) image.at<Vec3b>(i,j)[1] << " " << (int) image.at<Vec3b>(i,j)[2] << std::endl;
                    }
                }
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
