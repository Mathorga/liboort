#include <dirent.h>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "utils.h"
#include "Synapse.h"
#include "SparsePerceptronModelParser.h"
#include "SparsePerceptronNetwork.h"
#include "Experience.h"
#include "Knowledge.h"
#include "KnowledgeParser.h"

#define OUTPUTS_NUM 3
#define VALUE_PRECISION 4

using namespace cv;

void readValuesFromName(Oort::Vector<neuron_value_t>* values, std::string fileName, std::string delimiter) {
    size_t pos = 0;

    while ((pos = fileName.find(delimiter)) != std::string::npos) {
        values->addLast(atof(("0." + fileName.substr(0, VALUE_PRECISION)).c_str()));
        fileName.erase(0, pos + delimiter.length());
    }
    values->addLast(atof(("0." + fileName.substr(0, 4)).c_str()));
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
    Mat image;
    Oort::Vector<neuron_value_t>* inputs = new Oort::Vector<neuron_value_t>();
    Oort::Vector<neuron_value_t>* outputs = new Oort::Vector<neuron_value_t>();
    Oort::Experience* expr;
    Oort::Knowledge* knowledge = new Oort::Knowledge(1296, 3);
    Oort::KnowledgeParser* knlParser = new Oort::KnowledgeParser();

    // Input check.
    if (argc > 2 || argc <= 1) {
        printf("Usage: %s [imagesDir]\n", argv[0]);
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
            // Only read well-named files.
            if (std::count(fileName.begin(), fileName.end(), valuesDelimiter.c_str()[0]) == 2 &&
                std::count(fileName.begin(), fileName.end(), formatDelimiter.c_str()[0]) == 1) {
                tmpFileName = fileName;

                // Get all values from the name.
                inputs->empty();
                outputs->empty();
                readValuesFromName(outputs, fileName, valuesDelimiter);

                // Open the file and manage it.
                std::cout << fileName << std::endl;

                // Read file.
                image = imread(knowledgePath + fileName);

                // Read single pixels.
                for (int i = 0; i < image.rows; i++) {
                    for (int j = 0; j < image.cols; j++) {
                        // You can now access the pixel value with cv::Vec3b
                        // std::cout << (int) image.at<Vec3b>(i,j)[0] << " " << (int) image.at<Vec3b>(i,j)[1] << " " << (int) image.at<Vec3b>(i,j)[2] << std::endl;
                        inputs->addLast(image.at<Vec3b>(i,j)[0] / 256.0);
                        inputs->addLast(image.at<Vec3b>(i,j)[1] / 256.0);
                        inputs->addLast(image.at<Vec3b>(i,j)[2] / 256.0);
                    }
                }
                expr = new Oort::Experience();
                expr->setInputs(inputs);
                expr->setOutputs(outputs);
                expr->print();
                knowledge->addExperience(expr);
            }
        }
        if (knowledge->getExperiencesNum() > 0) {
            knowledge->print();
            knlParser->setKnowledge(knowledge);
            knlParser->writeFile((char*) "./res/knl/Oort2.knl");
        }
    }

    closedir(knowledgeDir);

    return 0;
}
