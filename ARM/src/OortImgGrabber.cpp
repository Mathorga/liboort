#include "opencv2/opencv.hpp"
#include "utils.h"

#define COUNT_DIGITS 10
#define PATH_CHARS_NUM 100

using namespace cv;

int main(int argc, char const *argv[]) {
    double startTime = 0;
    double endTime = 0;
    double execTime = 0;
    char* destDirPath = (char*) "";
    char saveFilePath[PATH_CHARS_NUM];
    int imageNumber = 0;
    char imageNumberStr[COUNT_DIGITS];
    VideoCapture cap(0);
    Mat showFrame;
    Mat saveFrame;
    bool running = true;

    // Input check.
    if (argc > 2 || argc <= 1) {
        printf("Usage: %s [destinationDir]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        destDirPath = (char*) argv[1];
    }


    cap.set(CAP_PROP_FRAME_WIDTH, 160);
    cap.set(CAP_PROP_FRAME_HEIGHT, 120);

    // Check if VideoCapture opened successfully.
    if (!cap.isOpened()) {
        printf("Error opening video stream or file\n");
        return -1;
    }

    while (running) {

        startTime = getTime();

        // Capture frame-by-frame
        cap >> showFrame;

        // If the frame is empty, break immediately
        if (showFrame.empty()) {
            break;
        }

        // Crop the frame.
        // Rect rectCrop(20, 0, 140, 120);
        // frame = frame(rectCrop);

        // Turn frame to grayscale.
        // cvtColor(showFrame, showFrame, COLOR_BGR2GRAY);
        // Resize the frame.
	resize(showFrame, saveFrame, Size(24, 18));
        resize(saveFrame, showFrame, Size(), 10, 10, INTER_NEAREST);

        // printf("A pixel of the frame: %d - %d - %d\n", frame.at<Vec3b>(10, 10).val[0], frame.at<Vec3b>(10, 10).val[1], frame.at<Vec3b>(10, 10).val[2]);

        // Display the resulting frame
        imshow("Show", showFrame);
        // imshow("Save", saveFrame);

        endTime = getTime();
        execTime = endTime - startTime;

        // Press ESC on keyboard to exit.
        char c = (char) waitKey(25);
        switch (c) {
            case 114:
                // Write down the picture.
                strcpy(saveFilePath, destDirPath);
                snprintf(imageNumberStr, COUNT_DIGITS, "%d", imageNumber);
                strcat(saveFilePath, imageNumberStr);
                strcat(saveFilePath, ".jpg");
                imwrite(saveFilePath, saveFrame);
                printf("\n%s\n", saveFilePath);
                imageNumber++;
                break;
            case 27:
                running = false;
                break;
            default:
                printf("Time: %f s\n", execTime);
                break;
        }
        // if (c == 27) {
        //     break;
        // }
    }
    // When everything done, release the video capture object.
    cap.release();

    // Closes all the frames.
    destroyAllWindows();

    return 0;
}
