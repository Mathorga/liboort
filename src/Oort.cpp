#include <opencv2/opencv.hpp>
#include "SparsePerceptronNetwork.h"
#include "SparsePerceptronModelParser.h"
#include "SerialNerve.h"
#include "utils.h"

#define CAPTURE_WIDTH 160
#define CAPTURE_HEIGHT 120
#define FINAL_WIDTH 24
#define FINAL_HEIGHT 18
#define IMAGE_DEPTH 3

using namespace cv;

int main(int argc, char const *argv[]) {
    double startTime = 0;
    double endTime = 0;
    char* modelFileName = nullptr;
    Oort::SparsePerceptronNetwork* brain = nullptr;
    Oort::SparsePerceptronModelParser* modelParser = new Oort::SparsePerceptronModelParser();
    VideoCapture eye(0);
    Mat tmpImage;
    Mat image;
    Oort::Vector<neuron_value_t>* data = new Oort::Vector<neuron_value_t>(FINAL_WIDTH * FINAL_HEIGHT * IMAGE_DEPTH);
    bool preview = false;

    // Input check.
    if (argc > 3 || argc <= 1) {
        printf("Usage: %s [-p] [modelFileName]\n", argv[0]);
        return -1;
    }
    if (argc > 2) {
        if (!strcmp((char*) argv[1], "-p")) {
            preview = true;
            modelFileName = (char*) argv[2];
        } else {
            printf("Usage: %s [-p] [modelFileName]\n", argv[0]);
            return -1;
        }
    } else if (argc > 1) {
        modelFileName = (char*) argv[1];
    }

    // Read specified model file.
    modelParser->readFile(modelFileName);

    // Set the brain model based on that read before.
    brain = new Oort::SparsePerceptronNetwork(modelParser->getModel());

    // Set default capture size.
    eye.set(CV_CAP_PROP_FRAME_WIDTH, CAPTURE_WIDTH);
    eye.set(CV_CAP_PROP_FRAME_HEIGHT, CAPTURE_HEIGHT);

    // Check if VideoCapture opened successfully.
    if (!eye.isOpened()) {
        printf("\nError opening eye\n");
        return -1;
    }

    // Main loop of the program.
    for (uint8_t i = 0;; i ++) {
        //TODO Get input from the nerve.

        startTime = Oort::getTime();

        // Capture frame-by-frame
        eye >> tmpImage;

        // If the frame is empty, break immediately
        if (tmpImage.empty()) {
            break;
        }

        // Downscale the image to feed it to the brain.
        resize(tmpImage, image, Size(FINAL_WIDTH, FINAL_HEIGHT));

        if (preview) {
            // Upscale the image to show it on screen.
            resize(image, tmpImage, Size(), 10, 10, INTER_NEAREST);

            // Display the resulting frame
            imshow("Preview", tmpImage);
        }
        // Press ESC on keyboard to exit.
        char c = (char) waitKey(25);
        if (c == 27) {
            break;
        }

        // Convert image data to brain input data.
        for (int32_t i = 0; i < image.rows; i++) {
            for (int32_t j = 0; j < image.cols; j++) {
                for (int32_t k = 0; k < IMAGE_DEPTH; k++) {
                    // You can now access the pixel value with cv::Vec3b
                    data->replaceAt(image.at<Vec3b>(i,j)[k] / 256.0, IDX(i, (j * IMAGE_DEPTH) + k, image.cols * IMAGE_DEPTH));
                }
            }
        }

        // Feed the captured image to the brain.
        brain->setInput(data);
        brain->run();

        // Sleep for a while.
        usleep(5000);

        endTime = Oort::getTime();

        printf("\nOutput %f %f %f\n", brain->getOutput()[0], brain->getOutput()[1], brain->getOutput()[2]);
        // printf("Elapsed time %f\n", endTime - startTime);
        printf("Framerate %d\n", (int) (1 / (endTime - startTime)));

        //TODO Send output to the nerve.
    }

    // When everything done, release the video capture object.
    eye.release();

    // Closes all the frames.
    destroyAllWindows();

    return 0;
}
