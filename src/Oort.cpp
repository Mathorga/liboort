#include <opencv2/opencv.hpp>
#include "SparsePerceptronNetwork.h"
#include "SparsePerceptronModelParser.h"
#include "utils.h"

#define CAPTURE_WIDTH 160
#define CAPTURE_HEIGHT 120
#define FINAL_WIDTH 24
#define FINAL_HEIGHT 18

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
    Oort::Vector<neuron_value_t>* data = nullptr;

    // Input check.
    if (argc > 2 || argc <= 1) {
        printf("Usage: %s [modelFileName]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
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
        printf("\nError opening video stream or file\n");
        return -1;
    }

    // Main loop of the program.
    for (uint16_t i = 0;; i ++) {
        //TODO Get input from the nerve.

        startTime = Oort::getTime();

        // Capture frame-by-frame
        eye >> tmpImage;

        // If the frame is empty, break immediately
        if (tmpImage.empty()) {
            break;
        }

        // Resize the frame.
        resize(tmpImage, image, Size(FINAL_WIDTH, FINAL_HEIGHT));
        resize(image, tmpImage, Size(), 10, 10, INTER_NEAREST);

        // Display the resulting frame
        imshow("Show", tmpImage);

        // Press ESC on keyboard to exit.
        char c = (char) waitKey(25);
        if (c == 27) {
            break;
        }

        // Convert image data to brain input data.
        data = new Oort::Vector<neuron_value_t>();
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                // You can now access the pixel value with cv::Vec3b
                data->addLast(image.at<Vec3b>(i,j)[0] / 256.0);
                data->addLast(image.at<Vec3b>(i,j)[1] / 256.0);
                data->addLast(image.at<Vec3b>(i,j)[2] / 256.0);
            }
        }

        // Feed the captured image to the brain.
        brain->setInput(data->getItems());
        brain->run();

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
